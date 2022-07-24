# ランダムマップ生成プログラム
本プログラムは，区域分割法によりランダムなマップ生成を行います．そして，生成過程を描画してくれます．

実装言語はc++です．

開発は，Visual Studio 2019で行いました．

描画ライブラリとして，[DXライブラリ](https://dxlib.xsrv.jp/index.html)を用いました．

# 区域分割法のアルゴリズム
区域分割法は，まず，マップ全体を複数のエリアに分けます，その後，エリアごとに部屋を生成します．そして，作成した部屋から通路を伸ばし，部屋同士を繋ぎます．

実装方針の一例として，

1. マップ全体を壁で埋める．

<img src="https://github.com/alain0077/study_c/blob/images/c%2B%2B/Create_Map_For_Roguelike/algorithm1.png" width="320px" alt="Algorithm 1" title="Algorithm 1">

1. 縦か横にラインを引いて2分割する．

<img src="https://github.com/alain0077/study_c/blob/images/c%2B%2B/Create_Map_For_Roguelike/algorithm2.png" width="320px" alt="Algorithm 2" title="Algorithm 2">

1. 分けたエリア内に収まる部屋を作成．

<img src="https://github.com/alain0077/study_c/blob/images/c%2B%2B/Create_Map_For_Roguelike/algorithm3.png" width="320px" alt="Algorithm 3" title="Algorithm 3">

1. 部屋から境界まで通路を伸ばす．

<img src="https://github.com/alain0077/study_c/blob/images/c%2B%2B/Create_Map_For_Roguelike/algorithm4.png" width="320px" alt="Algorithm 4" title="Algorithm 4">

1. 境界上の通路を繋げば，マップ完成！

<img src="https://github.com/alain0077/study_c/blob/images/c%2B%2B/Create_Map_For_Roguelike/algorithm5.png" width="320px" alt="Algorithm 5" title="Algorithm 5">

ラインを引く位置をランダムにしてやれば，実行毎に違うマップを作成できるはず…






ローグライクゲーでよく見かける自動生成ダンジョン．それらを作成するためのアルゴリズムは複数存在するらしい…今回はその内の1つであるを区分分割法について実装した．