#ifndef BASE_SOFT_STRIP_H_
#define BASE_SOFT_STRIP_H_

// #include "base/memory/ref_counted.h"
// #include "base/basictypes.h"
//#include "base/compiler_specific.h"
//#include "base/single_thread_task_runner.h"
// #include "base/threading/thread_checker.h"
#include "soft_controller.h"
#include "abstract_soft_strip_view.h"
#include <vector>
//#include "base/memory/scoped_ptr.h"

class BaseSoft;
class WindowsView;
class SoftDataController;

class BaseSoftStrip :
	public AbstractSoftStripView,
	public SoftController{
public:
	BaseSoftStrip();
	virtual ~BaseSoftStrip();

	typedef std::vector<BaseSoft*> SoftList;

	virtual void ChangeSoft(BaseSoft *soft);
	virtual void DeleteSoft(BaseSoft * soft);
	virtual bool DownloadSoft(BaseSoft *soft);
	//
	virtual  void set_windows_view(WindowsView *view);
	virtual  WindowsView *windowview();
	virtual  void LoadStripView();
private:
	WindowsView *view_;
	SoftList soft_list_;
	std::auto_ptr<SoftDataController> soft_data_controller_;
};

#endif

