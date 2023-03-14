#include <stdio.h>
#include <stdlib.h>

#include "test.hpp"



int main(int argc, char** argv){
	
	CKCoreApplicationSettings *settings = new CKCoreApplicationSettings();
	TestCore *core = new TestCore(settings);
	core->start();
	
	delete core;
	delete settings;
	
	return 0;
}
