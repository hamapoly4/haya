#include "Scenario.h"
#include <stdio.h>

Scenario::Scenario()
	: mscene_no(TOP), mscene_switch_flag(false), mscenario_fin_flag(false)
{
	mScene[TOP] = new Scene(mscene_no);	// シーン①を確保
}

Scenario::~Scenario()
{
	delete mScene[LAST];				// シーン⑯を解放

	printf("シナリオオブジェクトの解放！！\n");
}

void Scenario::run()
{
	mScene[mscene_no]->run();
	mscene_switch_flag = mScene[mscene_no]->fin_judge();
	switch_scene();
}

void Scenario::switch_scene()
{
	if (mscene_switch_flag == true)
	{
		if (mscene_no >= LAST)
		{
			mscenario_fin_flag = true;
		}
		else
		{
			delete mScene[mscene_no];
			mscene_no++;
			mScene[mscene_no] = new Scene(mscene_no);
			mscene_switch_flag = false;
		}
	}
}

bool Scenario::finish()
{
	return mscenario_fin_flag;
}
