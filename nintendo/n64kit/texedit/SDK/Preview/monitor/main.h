/*
   main.h

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#ifndef MAIN_H
#define MAIN_H

#ifdef _LANGUAGE_C

/* Define external variables */
/* <<< 外部変数の定義 >>> */
/* Variables common to the main routine and the callback 
   are made "volatile" so they are optimized and not deleted */
/* <<< メインルーチンとコールバックで共用する変数には
   最適化されて消されないよう volatile をつける。>>> */
extern volatile int stage;

/* Read Controller data */
/* <<< コントローラ読取データ >>> */
extern NUContData	contdata[1];

#endif /* _LANGUAGE_C */
#endif /* MAIN_H */
