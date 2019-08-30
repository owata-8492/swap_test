# swap_test
swap_ioシステムコールのテスト用プログラム
 + printA.c fpへ'A'を100回出力．3秒待ってfpへ'A'を100回出力．出力先はout/out1.txt
 + printB.c fpへ'B'を100回出力．3秒待ってfpへ'B'を100回出力．出力先はout/out2.txt
 + swapper.c forkして子プロセス1でprintAを実行．親プロセスにて再びforkし子プロセス2でprintBを実行．親プロセスにて1秒待ってswap_ioシステムコールを実行

　swapper.cの実行ファイル実行後に出力を確認し，out1.txtが"AAA...BBB..."，out2.txtが"BBB...AAA..."なら成功
 
# バグ？
 + printAのpidの取得をprintAの子プロセス開始後(=0が入る)，printBのpidの取得を親プロセスの最初(=printAのpidが入る)としてしまっていた(修正済)．このとき，swap_ioシステムコールの返り値として2が返ってきた．0が交換失敗，１が交換成功であり仕様外の値．
 + 出力結果について，返り値は0(=交換失敗)であるがout1.txtが"BBB...BBB..."，out2.txtが"AAA...AAA..."となっている．システムコール実行部分をコメントアウトすると想定通り"AAA...AAA..."，"BBB...BBB..."となるので何らかの処理を勝手にしているのではないかと考えられる．

# 現状
 swap_ioシステムコールの返り値は0(交換失敗)である
