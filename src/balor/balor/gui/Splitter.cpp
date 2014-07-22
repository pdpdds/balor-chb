#include "Splitter.hpp"

#include <utility>

#include <balor/graphics/Brush.hpp>
#include <balor/graphics/Cursor.hpp>
#include <balor/graphics/Graphics.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/verify.hpp>
#include <balor/Flag.hpp>
#include <balor/scopeExit.hpp>


namespace balor {
	namespace gui {

using std::move;
using namespace balor::graphics;


namespace {
} // namespace



Splitter::Splitter()
	: _movable(false)
	, _zOrderable(false)
	, _margin(0)
	{
}


Splitter::Splitter(Splitter&& value, bool checkSlicing)
	: Control(move(value))
	, _movable(move(value._movable))
	, _zOrderable(move(value._zOrderable))
	, _margin(move(value._margin))
	, _onPaint(move(value._onPaint))
	{
	if (checkSlicing) {
		assert("Object sliced" && typeid(*this) == typeid(value));
	}
}


Splitter::Splitter(Control& parent, int x, int y, int width, int height, Control::Edge edge)
	: _movable(false)
	, _zOrderable(false)
	, _margin(0)
	{
	int exStyle = 0;
	int style = WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
	switch (edge) {
		case Edge::line   : style |= WS_BORDER; break;
		case Edge::sunken : exStyle |= WS_EX_STATICEDGE; break;
		case Edge::client : exStyle |= WS_EX_CLIENTEDGE; break;
	}
	attachHandle(CreateWindowExW(exStyle, userClassName(), nullptr, style
		, x, y, width, height, parent, nullptr, nullptr, nullptr));
}


Splitter::~Splitter() {
}


Splitter& Splitter::operator=(Splitter&& value) {
	if (&value != this) {
		this->~Splitter();
		new (this) Splitter(move(value));
	}
	return *this;
}


void Splitter::bounds(const Rectangle& value) {
	_movable = true;
	scopeExit([&] () {
		_movable = false;
	});
	Control::bounds(value);
}


Control::Edge Splitter::edge() const {
	return _handle.edge();
}


void Splitter::edge(Control::Edge value) {
	_handle.edge(value);
}


bool Splitter::focusable() const {
	return false; // �����L�[�Ńt�H�[�J�X�𓾂Ȃ��悤�ɏ㏑���B
}


Padding Splitter::margin() const {
	return _margin;
}


void Splitter::margin(const Padding& value) {
	_margin = value;
}


Listener<Splitter::Paint&>& Splitter::onPaint() { return _onPaint; }


void Splitter::position(const Point& value) {
	_movable = true;
	scopeExit([&] () {
		_movable = false;
	});
	Control::position(value);
}


bool Splitter::vertical() const {
	auto size = this->size();
	return size.width < size.height;
}


void Splitter::zOrder(int value) {
	_zOrderable = true;
	scopeExit([&] () {
		_zOrderable = false;
	});
	Control::zOrder(value);
}


void Splitter::processMessage(Message& msg) {
	switch (msg.message) {
		case WM_ERASEBKGND : {
			if (onPaint() || brush()) {
				msg.result = TRUE;
			} else {
				processMessageByDefault(msg);
			}
		} break;
		case WM_NCHITTEST : {
			msg.result = HTCAPTION; // �S�̂��^�C�g���o�[�Ƃ݂Ȃ��ăh���b�O�ړ��ł���悤�ɂ���B
		} break;
		case WM_PAINT : {
			PAINTSTRUCT paint;
			Graphics graphics(BeginPaint(handle(), &paint));
			scopeExit([&] () {
				EndPaint(handle(), &paint);
			});
			if (onPaint()) {
				Paint event(*this, graphics);
				onPaint()(event);
			} else {
				auto brush = this->brush();
				if (brush) {
					auto displayRect = displayRectangle();
					const auto origin = graphics.brushOrigin(graphics.brushOrigin() + displayRect.position() + brushOrigin());
					brush = graphics.brush(brush);
					displayRect.grow(1, 1);
					graphics.drawRectangle(displayRect);
					graphics.brushOrigin(origin);
					graphics.brush(brush);
				} 
			}
		} break;
		case WM_PRINTCLIENT : {
			if (onPaint()) {
				Paint event(*this, (HDC)msg.wparam);
				onPaint()(event);
			}
			processMessageByDefault(msg);
		} break;
		case WM_SETCURSOR : {
			Mouse::cursor(vertical() ? Cursor::sizeWE() : Cursor::sizeNS());
		} break;
		case WM_WINDOWPOSCHANGING : {
			auto info = (WINDOWPOS*)msg.lparam;
			if (!_zOrderable) { // �h���b�O����ƍőO�ʂɈړ�����̂�j�~����BDockLayout �Ń��C�A�E�g���ω����Ă��܂��̂ŁB
				info->flags |= SWP_NOZORDER;
			}
			if (!toFlag(info->flags)[SWP_NOMOVE] && !_movable) {
				auto bounds = this->bounds();
				Point newPosition(info->x, info->y);
				if (newPosition != bounds.position()) {
					auto vertical = this->vertical();
					// �ړ��𐂒��܂��͐����ɐ�������
					if (vertical) {
						newPosition.y = bounds.y;
					} else {
						newPosition.x = bounds.x;
					}
					auto diff = newPosition - bounds.position();
					auto parent = this->parent();
					assert(parent);
					// �ړ��ʒu�����E����݂͂ł�̂�j�~����B
					for (auto i = parent->controlsBegin(); i; ++i) {
						auto childBounds = i->bounds();
						if (vertical) {
							if (bounds.top() <= childBounds.top() && childBounds.bottom() <= bounds.bottom()) {
								// ���ɐڂ��邩�ǂ���
								if (childBounds.right() == bounds.left()) {
									// ���ɂ݂͂ł邩�ǂ���
									if (childBounds.width  + diff.x < _margin.left ) {
										newPosition.x = childBounds.left() + _margin.left;
										diff.x = newPosition.x - bounds.x;
									}
								}
								// �E�ɐڂ��邩�ǂ���
								if (childBounds.left() == bounds.right()) {
									// �E�ɂ݂͂ł邩�ǂ���
									if (childBounds.width  - diff.x < _margin.right) {
										newPosition.x = childBounds.right() - _margin.right - bounds.width;
										diff.x = newPosition.x - bounds.x;
									}
								}
							}
						} else {
							if (bounds.left() <= childBounds.left() && childBounds.right() <= bounds.right()) {
								// ��ɐڂ��邩�ǂ���
								if (childBounds.bottom() == bounds.top()) {
									// ��ɂ݂͂ł邩�ǂ���
									if (childBounds.height + diff.y < _margin.top  ) {
										newPosition.y = childBounds.top() + _margin.top;
										diff.y = newPosition.y - bounds.y;
									}
								}
								// ���ɐڂ��邩�ǂ���
								if (childBounds.top() == bounds.bottom()) {
									// ���ɂ݂͂ł邩�ǂ���
									if (childBounds.height - diff.y < _margin.bottom) {
										newPosition.y = childBounds.bottom() - _margin.bottom - bounds.height;
										diff.y = newPosition.y - bounds.y;
									}
								}
							}
						}
					}
					// �ڂ��Ă���R���g���[���̑傫����ς���B
					for (auto i = parent->controlsBegin(); i; ++i) {
						auto childBounds = i->bounds();
						if (vertical) {
							if (bounds.top() <= childBounds.top() && childBounds.bottom() <= bounds.bottom()) {
								// ���ɐڂ��邩�ǂ���
								if (childBounds.right() == bounds.left()) {
									childBounds.width  += diff.x;
									i->bounds(childBounds);
								}
								// �E�ɐڂ��邩�ǂ���
								if (childBounds.left() == bounds.right()) {
									childBounds.x += diff.x;
									childBounds.width  -= diff.x;
									i->bounds(childBounds);
								}
							}
						} else {
							if (bounds.left() <= childBounds.left() && childBounds.right() <= bounds.right()) {
								// ��ɐڂ��邩�ǂ���
								if (childBounds.bottom() == bounds.top()) {
									childBounds.height += diff.y;
									i->bounds(childBounds);
								}
								// ���ɐڂ��邩�ǂ���
								if (childBounds.top() == bounds.bottom()) {
									childBounds.y += diff.y;
									childBounds.height -= diff.y;
									i->bounds(childBounds);
								}
							}
						}
					}
					// �ŏI�I�Ȉړ����ݒ�
					info->x = newPosition.x;
					info->y = newPosition.y;
				}
			}
			Control::processMessage(msg);
		} break;
		default: {
			Control::processMessage(msg);
		} break;
	}
}



	}
}