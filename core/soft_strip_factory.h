#ifndef SOFT_STRIP_FACTORY_H_
#define SOFT_STRIP_FACTORY_H_

class AbstractSoftStripView;
class WindowsView;

AbstractSoftStripView *CreateSoftStrip(WindowsView *view);

#endif
