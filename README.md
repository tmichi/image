画像処理自習教材
=====

目的
-----
C++またはJavaプログラムの書き方について，画像処理を題材に学ぶことを目的とする． 画像処理を題材にしたのは，研究室でCT画像を扱っているので，その導入と， 結果を画像として確認できることで文字列で Hello World と打つよりは動機付けになると考えたためである．

ダウンロード
-----
- https://github.com/tmichi/image/releases/tag/v.20160413

コンパイル
-----
doc/ip_intro.pdfを参照のこと．

課題 
-----

必要な関数は，インターネットで探すか，自分で作成すること．また，アルゴリズムについては，「ディジタル画像処理」という本が参考になる．
- ガウスフィルタをかけるプログラムを作成すること．
- 画像をθ分だけ回転させるプログラムを作成すること．ただしθは，引数で与えるものとする．また，元画像は，はみ出ないようにすること．
- 白黒画像を連結成分でラベリングするプログラムを作成すること．

Minimum codes for studying image processing in C++ and Java
=====

Objective
-----
The objective of this codes is learn how to write C++ or Java codes using sample image processing codes. 
Since our laboratory uses CT images, I believe this code will be a good example for programming rather than "Hello world"-like codes. 

Download
-----
- https://github.com/tmichi/image/releases/tag/v.20160413

Build and Run
-----
See cpp/README.txt or java/README.txt.

Assignments 
-----

- Implement Gaussian filter. 
- Implement Rotation of images. Rotation angle must be given in runtime, and the rotated images must be changed so that all pixels are drawn in the image. 
- Implement connected component labelling of binary images. 

Ask google if unknown words are found. 
