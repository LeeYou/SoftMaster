#ifndef WINDOWS_VIEW_H_
#define WINDOWS_VIEW_H_

class WindowsView
{
public:
	virtual HWND GetNativeHwnd() const = 0;
};

#endif
