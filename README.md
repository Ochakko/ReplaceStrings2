# ReplaceStrings2
For operations of strings of XML file. Relace strings between two tags.

オープンソースです。
ライセンスはGPLlv2です。
著作権はおちゃっこLABにあります。

ReplaceStrings2はXMLファイルの操作用に作成しました。
ファイルをCXMLIOBufというバッファクラスに読み込みます。
2つの指定文字列(タグを想定)の間のバッファをCXMLIOBufに切り出します。
切り出したバッファを元に変換処理などを行います。

文字列のコピーや連結用にstrs.cppを使用しています。
dstの長さを越えないように処理します。


2016/03/01 ReplaceStrings2レポジトリをGitHubに作成してpush  おちゃっこLAB 化け猫おちゃっこ
