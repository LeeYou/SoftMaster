#include "stdafx.h"
#include "soft_strip_factory.h"
#include "abstract_soft_strip_view.h"
#include "soft_strip.h"
#include "windows_view.h"

AbstractSoftStripView * CreateSoftStrip(WindowsView *view){
	BaseSoftStrip* softstrip = new SoftStrip();
	if (softstrip) {
		softstrip->set_windows_view(view);
	}
	return softstrip;
}