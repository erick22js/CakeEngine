#ifndef cakengine_resources_coreapplicationsettings_h
#define cakengine_resources_coreapplicationsettings_h

#include <CakeEngine/api.hpp>


class CKCoreApplicationSettings{
	
	friend class CKCore;
	
private:
	Int window_width = 1000;
	Int window_height = 576;
	
public:
	CKCoreApplicationSettings();
	
};


#endif // cakengine_resources_coreapplicationsettings_h
