# Shoot-Gaming
本プログラムは簡素なシューティングゲームです．

オブジェクト指向論について，学ぶために作成しました．

[exe.zip](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/exe.zip)にexeファイルがあります．

# Class
本プログラムで実装した一部のクラスについて簡単に説明．

本プログラムの設計は，[龍神録プログラミングの館](https://dixq.net/rp/index.html)を参考にさせていただきました．

## Looper
[ヘッダ](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Looper.h), [ソース](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Looper.cpp)

### メンバ
public:
+ Looper()
+ ~Looper()
+ loop() : bool
+ onSceneChanged(const eScene, const Parameter&, const bool) : void

private:
+ \_sceneStack : stack<shared\_ptr<AbstractScene>>
+ Fps \_fps;

### 主な役割・機能
ゲームのそれぞれの*Scene*を管理するクラス．関数**onSceneChanged**によって*Scene*の切り替えを行う．作成した*Scene*は**\_sceneStack**にスタックしていく．関数**onSceneChanged**はインターフェースクラス（純粋仮想関数を含むクラス）[IOnSceneChangedListener](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/IOnSceneChangedListener.h)のメンバ関数で，本クラスでオーバーライドされている．コンストラクタで受けっとっている引数で見られる型eSceneは，[こちら](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/eScene.h)で定義されている列挙型である．

## AbstractScene
[ヘッダ](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/AbstractScene.h), [ソース](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/AbstractScene.cpp)

### メンバ
protected:
+ \_implSceneChanged : IOnSceneChangedListener\*

public:
+ AbstractScene(IOnSceneChangedListener\* , const Parameter&)
+ ~AbstractScene()
+ update() : void
+ draw() const : void 

### 主な役割・機能
このクラスは，全てのゲームのそれぞれの*Scene*を管理するクラスが継承する**Abstract**（抽象）クラスである．各*Scene*クラスが持つべき最低限のモジュールを定義した関数である．関数**Update**は各シーンの更新処理を実装するための関数．関数**draw**は，各シーンの描画について実装するための関数．この2つの関数は，[Looper](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Looper.cpp)クラスによって，各**Scene**の更新処理として呼ばれる．メンバ変数**\_implSceneChanged**は，[Looper](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Looper.cpp)クラスから受け取ったポインタを保存しておく変数で，これを用いて*Scene*の切り替えを[Looper](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Looper.cpp)クラスに伝える．その時に，渡す引数[Parameter](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/Parameter.cpp)は，次に切り替える*Scene*に渡したい値をタグ付して保存できるクラスである．

## AbstractPalyer
[ヘッダ](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/AbstractPlayer.h), [ソース](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/AbstractPlayer.cpp)

### メンバ
protected:
+ \_shot_cnt : unsigned int
+ \_flag : int
+ \_lives : int
+ \_width : int
+ \_heigh : int
+ \_img : string 
+ \_x : double
+ \_y : double
+ \_bltype : int
+ \_color : int
+ \_ptr : IShootListener\*

public:
+ AbstractPlayer(IShootListener\*, double , double, int, string)
+ ~AbstractScene()
+ init() : void;
+ update() : bool
+ draw() const : void
+ Edge() : vector<pair<Coor, Coor>>

### 主な役割・機能
このクラスは，全てのプレイヤーが操作するキャラを制御・管理するクラスが継承するための**Abstract**（抽象）クラスである．各派生クラスが持つべき最低限のモジュールを定義した関数である．関数**Update**は更新処理を実装するための関数．関数**draw**は，描画について実装するための関数．この2つの関数は，[PlayerMgr](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/PlayerMgr.cpp)クラスによって，更新処理として呼ばれる．メンバ変数**\_ptr**は，[PlayerMgr](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/PlayerMgr.cpp)クラスから受け取ったポインタを保存しておく変数で，これを用いてプレイヤーが*Shot*をしたときに弾の作成を[BulletMgr](https://github.com/alain0077/study_c/blob/master/c%2B%2B/Game/shoot-gaming/BulletMgr.cpp)クラスに依頼する．

# Refarence
- [DXライブラリ置き場](https://dxlib.xsrv.jp/index.html)

- [龍神録プログラミングの館](https://dixq.net/rp/index.html)

- [プログラミング入門サイト](https://bituse.info/game/shot/)