#include "stdafx.h"
#include "dungeonLoading.h"

HRESULT dungeonLoading::init()
{
	_loading = new loading;
	_loading->init();

	this->loadImage();
	this->loadSound();

	return S_OK;
}

void dungeonLoading::release()
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}

void dungeonLoading::update()
{
	_loading->update();
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("�븻����");
	}
}

void dungeonLoading::render()
{
	_loading->render();
}

void dungeonLoading::loadImage()
{
	_loading->loadImage("dungeonBack", "Images/����/dungeon_default37X21.bmp", 1280, 720);
	_loading->loadImage("dungeonSpa", "Images/����/dungeon_spa.bmp", 1280, 720);
	_loading->loadImage("dungeonSpaPixel", "Images/����/dungeon_spaPixcelCollision.bmp", 1280, 720);
	_loading->loadFrameImage("minimapEntranceH", "Images/����/minimapEntranceH.bmp", 20, 12, 2, 2);
	_loading->loadFrameImage("minimapEntranceW", "Images/����/minimapEntranceW.bmp", 12, 20, 2, 2);
	_loading->loadFrameImage("minimap", "Images/����/minimap.bmp", 172, 48, 2, 1);
	_loading->loadFrameImage("golemScroll", "Images/����/�񷽴�����ũ��11.bmp", 2277, 60, 11, 1);

	_loading->loadFrameImage("������", "Images/����/������.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������2", "Images/����/������2.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������3", "Images/����/������3.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������4", "Images/����/������4.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������5", "Images/����/������5.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("�����Ѹ�", "Images/����/�����Ѹ�.bmp", 105, 84, 1, 1);
	_loading->loadFrameImage("�����Ѹ�2", "Images/����/�����Ѹ�2.bmp", 84, 126, 1, 1);
	_loading->loadFrameImage("������Ʈ", "Images/����/������Ʈ.bmp", 280, 210, 1, 1);
	_loading->loadFrameImage("����å", "Images/����/����å.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("��������", "Images/����/��������.bmp", 70, 70, 1, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������������", "Images/����/������������14.bmp", 420, 38, 14, 1);

	_loading->loadFrameImage("����Ÿ��", "Images/����/����Ÿ��.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("�ܵ�Ÿ��", "Images/����/�ܵ�Ÿ��.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("¼��Ÿ��", "Images/����/¼��Ÿ��2.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);

	_loading->loadFrameImage("babySlime", "Images/����/babySlime9x4(2).bmp", 576, 256, 9, 4);
	_loading->loadFrameImage("bigSlime", "Images/����/BigSlime12x2.bmp", 984, 526, 12, 2);
	_loading->loadFrameImage("�񷽰���", "Images/����/GolemAttack13x4.bmp", 2470, 760, 13, 4);
	_loading->loadFrameImage("������", "Images/����/GolemMove8x4.bmp", 1520, 760, 8, 4);
	_loading->loadFrameImage("red�񷽰���", "Images/����/RedGolemAttack13x4.bmp", 2470, 760, 13, 4);
	_loading->loadFrameImage("red������", "Images/����/RedGolemMove8x4.bmp", 1520, 760, 8, 4);
	_loading->loadFrameImage("�񷽰����ǰ�", "Images/����/GolemAttackHit13x4.bmp", 2470, 760, 13, 4);
	_loading->loadFrameImage("�������ǰ�", "Images/����/GolemMoveHit8x4.bmp", 1520, 760, 8, 4);
	_loading->loadFrameImage("�׾Ƹ�", "Images/����/pot11x4.bmp", 519, 235, 11, 4);
	_loading->loadFrameImage("�׾Ƹ�Hit", "Images/����/pot11x4Hit.bmp", 519, 235, 11, 4);
	_loading->loadFrameImage("�׾Ƹ��Ѿ�H", "Images/����/potBulletH.bmp", 11, 34, 1, 2);
	_loading->loadFrameImage("�׾Ƹ��Ѿ�W", "Images/����/potBulletW.bmp", 17, 22, 1, 2);
	_loading->loadFrameImage("�ذ�����", "Images/����/skullHammerMove14X4.bmp", 2982, 688, 14, 4);
	_loading->loadFrameImage("�ذ������ǰ�", "Images/����/skullHammerMoveHit14X4.bmp", 2982, 688, 14, 4);
	_loading->loadFrameImage("�ذ����", "Images/����/skullHammerAttack22X4.bmp", 4686, 688, 22, 4);
	_loading->loadFrameImage("�ذ�����ǰ�", "Images/����/skullHammerAttackHit22X4.bmp", 4686, 688, 22, 4);
	_loading->loadFrameImage("������", "Images/����/gasManMove12.bmp", 1488, 472, 12, 4);
	_loading->loadFrameImage("�������ǰ�", "Images/����/gasManMoveHit12.bmp", 1488, 472, 12, 4);
	_loading->loadFrameImage("�����ǰ���", "Images/����/gasManAttack10.bmp", 1240, 472, 10, 4);
	_loading->loadFrameImage("�����ǰ����ǰ�", "Images/����/gasManAttackHit10.bmp", 1240, 472, 10, 4);
	_loading->loadFrameImage("����ȭ��W", "Images/����/gasArrowW.bmp", 48, 5, 2, 1);
	_loading->loadFrameImage("����ȭ��H", "Images/����/gasArrowH.bmp", 10, 24, 2, 1);
	_loading->loadFrameImage("enemyDie", "Images/����/enemyDie11.bmp", 1320, 136, 11, 1);
	_loading->loadFrameImage("potDie", "Images/����/potDie7(2).bmp", 602, 116, 7, 1);

	_loading->loadFrameImage("skeletonMove", "Images/����/bossSkeletonMove14X4.bmp", 2324, 621, 14, 4);
	_loading->loadFrameImage("skeletonMoveHitRed", "Images/����/bossSkeletonMove14X4HitRed.bmp", 2324, 621, 14, 4);
	_loading->loadFrameImage("skeletonMoveHitWhite", "Images/����/bossSkeletonMove14X4HitWhite.bmp", 2324, 621, 14, 4);
	_loading->loadFrameImage("skeletonAttackSword", "Images/����/bossSkeletonSword22X4.bmp", 3652, 621, 22, 4);
	_loading->loadFrameImage("skeletonAttackSwordHitRed", "Images/����/bossSkeletonSword22X4HitRed.bmp", 3652, 621, 22, 4);
	_loading->loadFrameImage("skeletonAttackSwordHitWhite", "Images/����/bossSkeletonSword22X4HitWhite.bmp", 3652, 621, 22, 4);
	_loading->loadFrameImage("skeletonAttackHammer", "Images/����/bossSkeletonHammer20X4.bmp", 3320, 621, 20, 4);
	_loading->loadFrameImage("skeletonAttackHammerHitRed", "Images/����/bossSkeletonHammer20X4HitRed.bmp", 3320, 621, 20, 4);
	_loading->loadFrameImage("skeletonAttackHammerHitWhite", "Images/����/bossSkeletonHammer20X4HitWhite.bmp", 3320, 621, 20, 4);
	_loading->loadFrameImage("hammerWave1", "Images/����/hammerWave(2)8.bmp", 1848, 251, 8, 1);
	_loading->loadFrameImage("skeletonBlade", "Images/����/bossSkeletonBlade8.bmp", 1040, 297, 8, 1);

	_loading->loadImage("enemyProgressBarFront", "Images/����/enemyProgressBarFront.bmp", 120, 10);
	_loading->loadImage("enemyProgressBarBack", "Images/����/enemyProgressBarback.bmp", 124, 14);
	_loading->loadImage("semiBossHpBarFront(red)", "Images/����/semiBossHpFront(red).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarFront(white)", "Images/����/semiBossHpFront(white).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarBack", "Images/����/semiBossHpBack.bmp", 947, 23, true, RGB(255, 0, 255));



	_loading->loadFrameImage("������(���Ʒ�)", "Images/����/dungeonDoorUD6.bmp", 1050, 212, 6, 2);
	_loading->loadFrameImage("������(�翷)", "Images/����/dungeonDoorLR6.bmp", 630, 350, 6, 2);
	_loading->loadFrameImage("�������Ѳ�(���Ʒ�)", "Images/����/dungeonDoorTopUD.bmp", 175, 212, 1, 2);
	_loading->loadFrameImage("�������Ѳ�(�翷)", "Images/����/dungeonDoorTopLR.bmp", 105, 350, 1, 2);
	_loading->loadFrameImage("������(���Ʒ�)", "Images/����/bossDoorH17.bmp", 1632, 54,17,1);
	_loading->loadFrameImage("������(�翷)", "Images/����/bossDoorW17.bmp", 918, 192,17,2);
	_loading->loadFrameImage("�������Ѳ�(�翷)", "Images/����/bossDoorTopW17.bmp", 54, 192,1,2);
	_loading->loadFrameImage("�������Ѳ�(���Ʒ�)", "Images/����/bossDoorTopH17.bmp", 96, 54,1,1);

	//�÷��̾� ����Ʈ
	_loading->loadFrameImage("ȭ������Ʈ", "Images/�÷��̾�/bowEffect.bmp", 240, 40, 3, 1);
	_loading->loadFrameImage("��������Ʈ", "Images/�÷��̾�/swordEffect 3X1.bmp", 240, 40, 3, 1);

}

void dungeonLoading::loadSound()
{
	_loading->loadSound("dungeonBGM", "Sound/����/dungeonBGM.mp3", true, true);
	_loading->loadSound("spaRoomBGM", "Sound/����/poolRoomBGM.mp3", true, true);
	_loading->loadSound("bossRoomBGM", "Sound/����/bossRoomBGM.mp3", true, true);


	_loading->loadSound("DungeonDoor", "Sound/door.wav");
	_loading->loadSound("bossDoor", "Sound/bossDoor.wav");
	_loading->loadSound("golemAttack", "Sound/���ʹ�/��/�񷽰���.wav");
	_loading->loadSound("golemHit", "Sound/���ʹ�/��/�񷽸���.wav");
	_loading->loadSound("potFire", "Sound/���ʹ�/��/�Ѿ˽��.wav");
	_loading->loadSound("potReload", "Sound/���ʹ�/��/�Ѿ�����.wav");
	_loading->loadSound("potBulletPop", "Sound/���ʹ�/��/�Ѿ�����.wav");
	_loading->loadSound("skullDie", "Sound/���ʹ�/����/golem_dungeon_king_golem_roar2-resources.assets-4536.wav");
	_loading->loadSound("skullAttackSword", "Sound/���ʹ�/�ذ�/skeletonAttackSword.wav");
	_loading->loadSound("skullAttackHammer", "Sound/���ʹ�/�ذ�/skeletonAttackHammer.wav");
	_loading->loadSound("skullHit", "Sound/���ʹ�/�ذ�/skeletonStep1.wav");
	_loading->loadSound("skullHit2", "Sound/���ʹ�/�ذ�/skeletonStep2.wav");
	_loading->loadSound("skullHit3", "Sound/���ʹ�/�ذ�/skeletonStep3.wav");
	_loading->loadSound("skeletonWave", "Sound/���ʹ�/�ذ�/wave.wav");
	_loading->loadSound("gasManHit", "Sound/���ʹ�/������/�����Ӹ���.wav");
	_loading->loadSound("golemDie", "Sound/���ʹ�/��/�񷽻��.wav");
	_loading->loadSound("enemyDie", "Sound/���ʹ�/������/����������.wav");
	_loading->loadSound("gasArrowPop", "Sound/���ʹ�/������/gasArrowPop.wav");

}
