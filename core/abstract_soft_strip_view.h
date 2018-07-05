#ifndef ABSTRACT_SOFT_STRIP_VIEW_H_
#define ABSTRACT_SOFT_STRIP_VIEW_H_

class WindowsView;

class AbstractSoftStripView
{
public:
	virtual ~AbstractSoftStripView(){}

	virtual  void LoadStripView() = 0;
	virtual  void set_windows_view(WindowsView *view) = 0;
	virtual  WindowsView *windowview() = 0;
};

#endif

