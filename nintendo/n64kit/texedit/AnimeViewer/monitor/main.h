/*
   main.h

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#ifndef MAIN_H
#define MAIN_H

#ifdef _LANGUAGE_C

/* Define external variables */
/* <<< �O���ϐ��̒�` >>> */
/* Variables common to the main routine and the callback 
   are made "volatile" so they are optimized and not deleted */
/* <<< ���C�����[�`���ƃR�[���o�b�N�ŋ��p����ϐ��ɂ�
   �œK������ď�����Ȃ��悤 volatile ������B>>> */
extern volatile int stage;

/* Read Controller data */
/* <<< �R���g���[���ǎ�f�[�^ >>> */
extern NUContData	contdata[1];

#define gStage	stage
#define	gContdata	contdata

#ifndef BOOL
#define BOOL u32
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif /* _LANGUAGE_C */
#endif /* MAIN_H */
