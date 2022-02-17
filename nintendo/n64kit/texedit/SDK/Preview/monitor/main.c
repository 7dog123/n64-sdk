/*
   main.c

   NuSYSTEM sample nu2

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).

 */

#include <nusys.h>
#include "main.h"

/* Stage number */
/* <<< �X�e�[�W�ԍ� >>> */
volatile int stage;

/* Declare prototypes */
/* <<< �v���g�^�C�v�錾 >>> */
void stage00(int);
void stage01(int);

/* Declare external functions */
/* <<< �O���֐��錾 >>> */
void initStage00(void);
void makeDL00(void);
void updateGame00(void);

void initStage01(void);
void makeDL01(void);
void updateGame01(void);

/* Read Controller 1 data */
/* <<< �P�R���g���[���ǎ�f�[�^ >>> */
NUContData	contdata[1];

/*------------------------
	Main
	<<< ���C�� >>>
--------------------------*/
void mainproc(void)
{
  /* Initialize graphic */
  /* <<< �O���t�B�b�N�̏����� >>> */
  nuGfxInit();

  /* Initialize controller manager */
  /* <<< �R���g���[���}�l�[�W���̏����� >>> */
  nuContInit();
	
  /* Set Stage number to 0*/
  /* <<< �X�e�[�W�ԍ����O�ɃZ�b�g����B>>> */
  stage = 0;

  while(1)
    {
      switch(stage)
	{
	  /* 
	     Register callback function corresponding to stage number.
	     On the callback function side,
	     set value in stage if a change in registration is
	     required in another callback function.
	     */
	  /* <<<
	     �X�e�[�W�ԍ��ɂ��A�Ή�����R�[���o�b�N�֐���o�^���܂��B
	     �R�[���o�b�N�֐����ł́A
	     ���̃R�[���o�b�N�֐��ɓo�^�ύX���K�v�ɂȂ������ɁA
	     stage �ɒl���Z�b�g���܂��B
	     >>> */
	case 0:
	  /* Set a value of -1 in stage in order to wait
	     for the value to be set in the callback function. */
	  /* <<< �R�[���o�b�N�֐����l���Z�b�g����̂�҂��߂ɁA
	     stage �̒l��-1�ɃZ�b�g���Ă����܂� >>>*/
	  stage = -1;
	  /* Initialize Stage 0 */
	  /* <<< �X�e�[�W�O�̏����� >>> */
	  initStage00();
	  /* Register callback */
	  /* <<< �R�[���o�b�N�o�^ >>> */
	  nuGfxFuncSet((NUGfxFunc)stage00);
	  /* Start display */
	  /* <<< �\���J�n >>> */
	  nuGfxDisplayOn();
	  break;
	case 1:
	  stage = -1;
	  initStage01();
	  nuGfxFuncSet((NUGfxFunc)stage01);
	  nuGfxDisplayOn();
	  break;
	default:
	  break;
	}
      
      /* Callback function waits for value to change (scene to change) */
      /* <<< �R�[���o�b�N�֐����l��؂�ւ���́i��ʐ؂�ւ��j��҂� >>> */
      while(stage == -1)
	;
      /* Turn off display */
      /* <<< �\�������� >>> */
      nuGfxDisplayOff();
    }
}


/*-----------------------------------------------------------------------------
  Callback function
  <<< �R�[���o�b�N�֐� >>>

  The value of pendingGfx, which is passed from Nusystem as an argument of the 
  callback function, is the sum of the currently processing and waiting to 
  process status of the RCP.
  <<< Nusystem ����R�[���o�b�N�֐��̈����Ƃ��ēn����� pendingGfx �� 
   ���ݏ���������я����҂��� RCP�^�X�N�̍��v���ł��B >>>
-----------------------------------------------------------------------------*/

/* Stage 0 */
/* <<< �X�e�[�W�O >>> */
void stage00(int pendingGfx)
{
  /* <<< �������^�����҂���RCP�^�X�N���Q�ȉ��ꍇ�A�\�������s�� >>> */
  if(pendingGfx < 3)
    makeDL00();		

  /* <<< �Q�[���i�s���� >>> */
  updateGame00(); 
}

/* <<< �X�e�[�W�P >>> */
void stage01(int pendingGfx)
{
  /* If the processing/waiting to process status of the RCP is 2 or less, perform display process */
  /* <<< �������^�����҂���RCP�^�X�N���Q�ȉ��ꍇ�A�\�������s�� >>> */
  if(pendingGfx < 3)
    makeDL01();

  /* Advance game process */
  /* <<< �Q�[���i�s���� >>> */
  updateGame01();
}
