---
title: "Raku言語って?"
---


# Raku言語って?

この章ではプログラミング言語Rakuについての歴史・言語的な特徴について見ていきます。
最も、 Raku言語としての時代があまり無いので、 大体はPerl6の言語を見ていく事になります。


# Rakuってどういう言語?


RakuはもともとPerl6と呼ばれていた言語で、 スクリプト言語に分類されるプログラミング言語です。
名前が変わったのは2019年であるため、 比較的最近から開発されているように感じますが、 実際は仕様は2000年に発表されている言語です。


## Perl5との簡単な比較

もともとPerl5は、 今までのPerl1などの後方互換性を重視していた結果、 オブジェクト指向などの機能が後付で入ってしまった経歴があります。
他にはPerl5特有の問題として、 `シジル`や`コンテキスト`が初心者には分かりづらいというものがありました。

例えばこのコードはPerl5で配列の0番目の要素を出力する例です。

```perl
my @array = (1..10);
print "$array[0]\n";
```

このコードに出てくる`@` と `$`はどのような意味を持つ記号でしょうか。

これは `$`が**スカラ変数を示すシジル**で、 `@`が**配列を示すシジル**となっています。
配列の中の1要素はスカラ変数だからシジルが$になるという具合です。

これをRakuで書いてみるとこういう記述になります。

```perl
my @array = (1..10);
@array[0].say;
```

Rakuにもシジルがあるみたいですが、 意味はPerl5と違うようです。
Perl5と比較して、 配列`@array`の1つの要素へのアクセスも、スカラ変数のシジル(`$`)ではなく、配列のシジルで要素にアクセスできるようになっています。


この他にも様々な違いがあります。例えばこの例題に関係するものですと次のようなものです。

- printに相当するのがsayで改行がもともと入っている
    - (Perl5にも存在しますが、 `use feature`する必要があります)
- sayはオブジェクトのメソッドとして定義されている


ということで、 Perl5のいいところを継承しつつ、 新しい言語としてデザインされている言語がプログラミング言語Rakuです。
他にはクラス定義の方法なども、 Perl5と比べてまるで異なります。

## なぜPerlの次期バージョンにならなかったのか

ではなぜRakuはPerlの次期バージョンにならなかったのでしょうか。

理由は様々ですが、一言で言うならばPerlと何もかもが違ったのが原因でしょう。
実はPerl6(Raku)は、 Perl5と雰囲気が似ているのは一部の構文だけで、 処理方法も実行環境も何もかもがPerl5とは違いがあったのです。
最初はPerl5のコードもPerl6で動くことを目標にしていましたが、 次第にそうではなくなってきてしまったのです。

Perl5は後方互換性を非常に重視する言語ですので、現在まだ広く使われているPerl5から、かなりの互換性を落としたPerl6への完全移行は抵抗があったのだと考えられます。
さらに処理系が発表された当初のPerl6は処理スピードが極端に遅く、 とてもPerlの次期バージョンとして満足に使える出来ではなかったのです。
また、 筆者がPerl6と出会った2016年ほどのタイミングでは、既にPerlとPerl6は別の言語という扱いでした。
「普段使用しているPerlはPerl5、 Perl6は別言語」というのが、PerlユーザーがPerl6について説明するお決まりのフレーズへと変化していきました。


しかしPerl5とPerl6(Raku)の関係が悪化しているかというとそういう訳ではありません。
例えば前述の行末に改行文字を自動で入れる`puts`のような関数`say`は、Perl6からPerl5に移植された機能の1つです。
他にはPerl5でリッチなOOPを行いたい場合によく使用されるM族モジュール(Moose, Moo, Mouse)などのアイディアのもともPerl6です。
Perl5とPerl6は現在のバージョン/次期バージョンとしての存在ではなく、共存する言語へとシフトしていきました。

そこでいわゆるPerlであるPerl5との名前を区別するために、 去年に言語の名前を変更する運動があって、 今はRakuに改名されました。
今は「Perl5」と「Raku」は別言語で、 それぞれ開発が進む方針になっているから、 Perl5の次バージョンというわけでは無くなったんだ。だけど今でもカンファレンスはRakuのカンファレンスとPerlのカンファレンスが同時開催されたり、 関係は良好だよ。 @<br>{}

//footnote[scalar_perl5][Perl5で「単一の値」を示すデータ型。文字列でも数値でもリファレンス(一種のポインタ)でもはいる]



## Rakuの仕様

@<B>{藍}: じゃぁ橙。次は Rakuの仕様の歴史について見ていこう。 Rakuは最初はドキュメントによる設計から始まった言語なんだ。
 これはRakuが「仕様と実装を明確に分離した言語」@<fn>{jisou_siyou}であることにも繋がるよ。

Perl5では仕様と実装が同一であるので、 Cで記述されたPerlインタプリタが仕様であり実装でもある

### Apocalypse(黙示録)

@<B>{藍}: Perl6の最初の設計は、 Perl5の作者と同じLarrryWallによって「@<kw>{Apocalypse,黙示録}」という一連の投稿で決定されたんだ。
この内容は現在でもrakuのドメイン上でアーカイブされている@<fn>{apocalypse}ので閲覧することができるよ。 @<br>{}

@<B>{橙}: アポカリプス! アポカリプスってなんか怖い名前ですね藍しゃま... @<br>{}

@<B>{藍}: 実はLarryはアポカリプスっていう名前は怖い意味じゃなくて、 Perl6の仕様を明らかにするという意味で使っていたみたいなんだ。 @<br>{}

> People get scared when they hear the word Apocalypse, but here I mean it in the good sense: a Revealing.
> An Apocalypse is supposed to reveal good news to good people.
>
> [Larry Wall, Apocalypse 1]

@<B>{藍}: 実際にLarryはこのアポカリプスでは、 Perl5までの問題点や良かったことを纏めつつ、 Perl6の言語デザインについて話しているんだ。
アポカリプス自体は8章存在しているよ。 @<br>{}

@<B>{橙}: あっ今ネットで見ていますがこの内容ですか?

 * Applocalypse1
 ** "The Ugly, the Bad, and the Good"
 * Applocalypse2
 ** "Bits and Pieces"
 * Apocalypse 3
 ** "Operators"
 * Apocalypse 4
 ** "Syntax"
 * Apocalypse 5
 ** "Pattern Matching"
 * Apocalypse 6
 ** "Subroutines"
 * Apocalypse 7
 ** "Formats" (see Exegesis 7)
 * Apocalypse 12
 ** "Objects"

中身を見てみると、いろんなIRCがセットになっているんですね! @<br>{}

@<B>{藍}: そうそう。このアポカリプスのあとに、 さらに文章が追加されるんだ

//footnote[apocalypse][@<href>{https://raku.org/archive/doc/apocalypse.html}]

=== Exegesis

@<B>{橙}:  そのあとに登場したのがこの@<kw>{Exegesis}@<fn>{Exegesis}ですか?   @<br>{}

@<B>{藍}:  そう。これはLarryではなくて、 Damian Conway 先生によって書かれた一連の文章だよ。
Damian Conway はPerlで書籍も出版していたり、 Perlプログラマの間では存在感のあるプログラマだね。
彼が出した一連のExegesisは、 LarryのアポカリプスよりさらにPerl6プログラムの構文や制御構造、 grammarに関するものなどが定義されてるよ。  @<br>{}

@<B>{橙}: ExegesisはExegesis 2, 3, 4, 5, 6の合計6つ存在するみたいですね!   @<br>{}

//footnote[Exegesis][@<href>{https://raku.org/archive/doc/exegesis.html}]


===  Synopsis & Perl6 Design Documents

@<B>{藍}: Rakuの仕様は「@<kw>{Perl6 Design Documents}@<fn>{perl6_design_doc}」に纏められたよ。
ここに書かれているpodで書かれた仕様を@<kw>{Synopsis}@<fn>{sinopsis}とも言うよ。
この内容自体は現在は更新されなくなっているので注意だよ。 @<br>{}

@<B>{橙}: よくブログやwebサイトで、このドキュメントへのリンクがあるのは、 長らくこのドキュメントが仕様だった時期があったからなんですね!

//footnote[sinopsis][@<href>{https://github.com/Raku/raku.org/tree/master/source/archive/doc/design/syn}]
//footnote[perl6_design_doc][@<href>{https://design.raku.org}]

===  Roast

@<B>{藍}: 今現在の仕様は公式テストスーツである「@<kw>{roast}」になっているんだ。だから文章というよりは書いてあるテストコードが仕様だよ。
仕様は必ずしも現在の実装が満たしているとは限らないから、 今Rakuのプログラミングをする上で必要な情報は公式ドキュメントを見ないと駄目なんだ。 @<br>{}

@<B>{橙}: こうしてRakuの言語仕様が決定したんですね!! なるほど!!! @<br>{}


//footnote[roast][@<href>{https://github.com/perl6/roast}]

== 実装の歴史

@<B>{藍}: Rakuは歴史的に色々な実装が登場しているよ。 というのも、 さっき一緒に見た通りもともと仕様から始まった言語というのが関係しているんだ。
これからは、 Raku(Perl6)の中でも代表的な実装を追っていこう。 @<br>{}

=== Pugs

@<B>{藍}: まずRaku、というかその前の名前のPerl6の実装を話す上で欠かせないのが@<kw>{Pugs}だね。
Pugsは一番最初に開発されたPerl6の処理系なんだ。開発者は@<kw>{唐鳳,オードリー・タン}さんだよ。  @<br>{}

@<B>{橙}: 台湾の方なんですね...! あ、この方最近ニュースで見た気がする...! @<br>{}

@<B>{藍}: 実は彼女は今は台湾のデジタル担当政務委員をしているんだ。日本で言うところのIT担当大臣だね。 @<br>{}

@<B>{橙}: だから前ニュースで見た覚えがあったんですね! なるほどです!! @<br>{}

@<B>{藍}: 彼女はまだ大臣じゃなかった2005年頃にPugsの実装を始めたんだ。
しかも当時勉強していた、覚えたてのHaskellで実装しているよ。
Pugsは現在は開発が止まっているけど、 プロジェクトのブログ@<fn>{pugs_blog}とCPAN@<fn>{cpan}上にpushされているPugsのリポジトリ@<fn>{pugs_cpan}を見ることができるよ。 @<br>{}

//footnote[pugs_blog][@<href>{https://pugs.blogs.com}]
//footnote[cpan][Perl5のモジュールがアップロードされるWebサービス]
//footnote[pugs_cpan][@<href>{https://metacpan.org/release/AUTRIJUS/Perl6-Pugs-6.2.12}]

@<B>{橙}: Pugsはどういうところがすごかったんですか? @<br>{}

@<B>{藍}: まずは今まで仕様だけで動かなかったPerl6がついに動く様になったんだ。 これで何人もの人々がPerl6に興味を持つきっかけになったみたいだよ。
他には仕様上の矛盾や、 絶対に無理がある構文などが、 Pugsを通して発見されたんだ。
 これはPugsの実装をテストするために、 Perl6のテストコードがいくつか書かれたからだと思うね。
だからPugsはPerl6の仕様そのものをアップデートする事にも貢献したことがすごいところかな。@<br>{}

=== Parrot

@<B>{藍}: 次に見ていくのは@<kw>{parrot}だよ。 日本ではYAPC::Asia@<fn>{yapc_asia}の時代にいくつかParrotを使ってみた発表があったかな。 @<br>{}

@<B>{橙}: 立派なオウムのアイコン!! これも今は開発は止まっているんですか? @<br>{}

@<B>{藍}: そうそう。 でもParrotで作られた実装のアイディアなどは現在の主力実装に転用されているよ。 @<br>{}

@<B>{橙}: おお!! 魂が受け継がれている感じがあってカッコいいですね...!! @<br>{}

@<B>{藍}: Parrot自体はもともとはエイプリルフールのネタとして発表されたらしいんだ。 でもその後本当に開発が進められた実装だよ。
Parrotの実装は、 Parrotという仮想的な機械の上でPythonやPerl6を実行してみようというアイディアだよ。
現在のRubyのYARV@<fn>{yarv}、 Pythonのpython vmなどと同様の、いわゆる@<kw>{プロセスVM}と呼ばれる実装手法かな。 @<br>{}

@<B>{橙}: Virtual BoxみたいなVMとは違うんですか? @<br>{}

@<B>{藍}: Virtual BoxみたいなVMは、 CPUは実在するものをマネして、 その上で他のOSとかを動かすVMだよね。
プロセスVMはあくまでもC言語とかのプログラムを実行するよ。
そのC言語のプログラムが実は仮想的なCPUのエミュレーターになっていて、 スクリプト言語がコンパイルされた仮想的な機械語がそのCPUエミュレータ上で実行される感じだよ。  @<br>{}

@<B>{橙}: なるほど! プログラミング言語ってそういう仕組だったんですね!! @<br>{}

@<B>{藍}: ParrotはParrotVMの上でPythonとPerl6を動かす様に設計されていたから、もちろんPerl6もParrotVM用の実装になっていたんだ。
じゃぁ橙私からの質問だ。 Perl6は何の言語で実装されていたと思う? @<br>{}

@<B>{橙}: う〜ん。 こういうスクリプト言語はだいたいC言語で実装されているイメージがあります! @<br>{}


@<B>{藍}: 惜しい!!
実はParrot自体はC言語で実装されていたけど、Perl6はC言語では実装されてないんだ。
Parrotは@<kw>{NQP}と呼ばれる別言語で実装されていたんだ。 @<br>{}

@<B>{橙}: えぬきゅーぴー...!? ですか? 新しい言語...? @<br>{}

@<B>{藍}: @<kw>{NQP,Not Quit Perl}、つまりPerlっぽい別の言語なんだ。 ParrotVMはPIRという中間コードを解釈するんだけど、これを生成するコンパイラはなるべく小さな状態にしたい。
そこで開発されたのがNQPなんだ。 NQPはPerl6よりはだいぶコンパクトな言語なんだけど、表現力は高い。NQPからPIRバイトコードを生成するとこを頑張って、 Perl6はNQPで実装すれば手間は省けるというわけなんだ。 @<br>{}

@<B>{橙}: なるほど! ということはNQPが読めればPerl6が読める...!! @<br>{}

@<B>{藍}: そういうことだね。このNQPの考えが、後のRakudoに繋がるよ。

//footnote[parrot][@<href>{http://parrot.org/}]
//footnote[yapc_asia][YAPC::Asia かつて日本で開催されていた大規模なPerlのお祭り。Perlに限らず様々なテックトークが行われた。今はYAPC::Japanとしてリブートしている]

//footnote[yarv][@<href>{http://www.atdot.net/yarv/}]

=== Rakudo

@<B>{藍}: さて橙、次はいよいよ現在の主力な実装の@<kw>{Rakudo}@<fn>{rakudo}について見ていくよ @<br>{}

@<B>{橙}: Rakudo!! 公式サイト見てたら神社の鳥居の絵に「楽土」とか書かれていて日本っぽいですね!! @<br>{}

@<B>{藍}: Rakudo自体はパラダイスの意味の「楽土」とか、 Perl5のマスコットがラクダだったから、武士道的な意味合いでラクダ道、 転じてRakudoにになったとも言われているよ。
言語の構成としてはさっきのParrotを受け継いでいて、ParrotVMの代わりに@<kw>{MoarVM}、 その上に@<kw>{NQP}と、 NQPで書かれたRakudoの3段セットになっているよ。

実はMoarVMの他にJavaのVMであるJavaVirtualMachine(JVM)やJavaScript上でも動く様に開発されているんだ。
とはいえ開発チームが力を主に注いでいるのはMoarVMだから、 MoarVMを使うのが無難だよ。
仕様と実装が分離しているRakuだけど、 現在使われている処理系はほぼこのRakudoだったりするんだ。

//footnote[rakudo][@<href>{https://rakudo.org/}]

==== MoarVM

@<B>{橙}: このMoarVMっていうのはなんですか? @<br>{}

@<B>{藍}: MoarVMは@<kw>{Metamodel On A Runtime Virtual Machine}の略で、 RakudoとサブセットのNQP用のVMのことだよ。
Parrotと同じ様な役割だけど、Parrotが汎用的なVMを目指していたのに対して、 MoarVMはRaku(Perl6)用に特化されているんだ。
具体的に言うと6modelというPerl6のオブジェクトモデルに準拠した形で実装が進められているから、 よりParrotより効率的に実装されているんだ。 @<br>{}

@<B>{橙}: なるほど! そういえば、このMoarVMはCで書かれているんですね! 言語っぽいです @<br>{}

@<B>{藍}: ちなみにここまでの話はgihyoの連載の「@<b>{モダンPerlの世界へようこそ}」の第14回「@<b>{Rakudo：実装する方法だってひとつではないのです}」に詳しいよ。@<br>{}


//footnote[modern_perl_raku][@<href>{https://gihyo.jp/dev/serial/01/modern-perl/0014}]

== なんで名前が変わったの?

@<B>{藍}: さて最初にも触れたけど、実はRakuは今まで紹介していたPerl6の名前が変わった言語だったんだ。
もともとはPerl5の後継として開発が進められてきた言語だけど、 かなりの部分違いが生じてきた。そのために姉妹言語としてPerlを使いの間では定着していたんだけど、 例えばPython2とPython3の関係性の様に誤解されることが多くなっていたんだ。 @<br>{}

@<B>{橙}: Python2とPython3は明確に次のバージョンという関係でしたけど、...! あっ、 「なんでPerl5をまだ使っているの? 時代はPerl6だよ?」みたいに思われちゃったんですね。 @<br>{}

@<B>{藍}: そうそう。それで「 "Perl" in the name "Perl 6" is confusing and irritating」というissue@<fn>{perl6_issue}がPerl6のリポジトリに出されたんだ。いくつか名前変更の案は出ていたけど、当初はPerl6のマスコットである蝶の名前「Camellia」とかが出ていたよ。
合わせて2019年のThePerlConference@<fn>{perlconf}やPerlCon@<fn>{perlcon_2019}でElizabeth Mattijsenさんによって「DeMythifying Perl 6@<fn>{demything}」というトークの中で名前変更が提案されていたんだ。
さっきのissueの中で、Damian Conway 先生によって提案された「Raku」@<fn>{perl6_issue_damian}が優勢になった。
RakuはもともとPerl6の愛称(エイリアス)としても使われていた名前でもあるから、 支持を集めやすかったのかなとか思うよ。さらに最終的にLarryWallからのコメントが付いた@<fn>{larry_issue}のが決定打になったね。
issueの議論が収まった後に、 Perl6メンテナたちの問題解決の協議に基づいて、 「The Path to Raku」@<fn>{peth_to_raku_md}と名前がついたRakuへの名前切り替え方針の指針がmergeされて、Rakuに正式に名前が変更されたんだ。


//footnote[perl6_irritating][@<href>{https://github.com/Raku/problem-solving/issues/81}]
//footnote[perlconf][アメリカで開催されるPerlの国際カンファレンス@<href>{https://perlconference.us/tpc-2019-pit/}]
//footnote[perlcon_2019][ヨーロッパ圏内で開催されるPerlの国際カンファレンス。内容は一部ThePerlConferenceと重複していたりする。 @<href>{https://perlcon.eu/}]
//footnote[demything][@<href>{https://www.youtube.com/watch?v=3vYIHw5rwgA}]
//footnote[perl6_issue][@<href>{https://github.com/Raku/problem-solving/issues/81}]
//footnote[perl6_issue_damian][@<href>{https://github.com/Raku/problem-solving/issues/81#issuecomment-520216578}]
//footnote[larry_issue][@<href>{https://github.com/Raku/problem-solving/pull/89#pullrequestreview-300789072}]
//footnote[peth_to_raku_md][@<href>{https://github.com/Raku/problem-solving/blob/master/solutions/language/Path-to-Raku.md}]



== 入門書

@<B>{橙}: Rakuって何か入門書って出てるんですかー? @<br>{}

@<B>{藍}: Rakuの入門書は海外では数冊出ているよ。 日本だと書籍では@<B>{雅なPerl入門の第3版}や@<B>{WEB+DB PRESSのPerl Hackers Hub}などで言及がある回があるくらいかな。
それ以外ならwebのエントリの形や@<B>{YAPC}や@<B>{各地のPM(Perl Mongers)}の登壇資料として発表されているものがあるかな。
日本語で読めるWebの入門記事は「Raku入門」@<fn>{perl_intro_ja_web}が体系的にまとまっていておすすめだよ。


//footnote[perl_intro_ja_web][@<href>{https://raku.guide/ja/}]


== コミュニティ

@<B>{藍}: 世界規模のものならIRC@<fn>{raku_irc_url}に参加すればいろいろ会話する事ができるよ。
Twitterで日本語でPerl6やRakuについてツイートした場合、 海外のRakuユーザーが翻訳してリプをしてくれたりするよ。
向こうの方々は日本語をGoogle翻訳とかを使って英語にした上で、 英語で返してくれるから、お互いに母国語でも会話することができるよ。 @<br>{}


@<B>{橙}: 日本では何かあるんですか? @<br>{}


@<B>{藍}: 日本国内ならゆーすけべー(@yusukebe)@<fn>{yusukebee}さんが主催しているrakulang-jp@<fn>{rakulang_jp}というslackワークスペースや、 YAPCや地域PMがコミュニティになっているよ。
基本的にはPerl5のコミュニティに行けば、Rakuのコミュニティに入る事ができるみたいなイメージだよ。

//footnote[raku_irc_url][@<href>{https://webchat.freenode.net/?channels=#raku}]
//footnote[yusukebee][@<href>{https://twitter.com/yusukebe}]
//footnote[rakulang_jp][@<href>{https://rakulang-jp.slack.com}]

== 情報を集めるなら

@<B>{橙}: Rakuのドキュメントとか、 いろいろな情報を集めるときはどうすれば良いんですか?
なんとなくRakuじゃなくてPerl6で検索すると色々出てきそうな気はしますが...!? @<br>{}

@<B>{藍}: 仕様自体はRoastに書かれているけど、 現在の実装に関したドキュメントは公式のwebドキュメント@<fn>{raku_documentation_web}を確認するのがおすすめだよ。
ネットの情報だと仕様の話と実装の話が同じエントリで話されていたりするんだ。
だから動かないソースコードとかが解説されているケースがあるよ。
他にはRakuの処理系がParrot時代だった頃の解説記事とかがあるから、 パフォーマンスや今のRakuで動くかどうかは試してみないとわからないんだ。
ブログとかを見るときは注意だね。 @<br>{}

@<B>{橙}: なるほど! ...あれっ、ドキュメントとかはドメインがrakuのものとperl6のものがありますね。どっちがいいんですか? @<br>{}

@<B>{藍}: 今はperl6ドメインからrakuドメインに移行しようとしているから、 同じようなサイトでrakuドメインのものがあるならrakuの方が最新版の可能性が高いよ。 @<br>{}

@<B>{橙}: 日本語記事だとどういうのがおすすめですか?  @<br>{}

@<B>{藍}: 日本語だとPerl6 AdventCalender@<fn>{perl6_advent_ja}などがおすすめだよ!  英語の方でもアドベントカレンダーは結構おすすめだよ。

//footnote[raku_documentation_web][@<href>{https://docs.raku.org/}]
//footnote[perl6_advent_ja][@<href>{https://qiita.com/advent-calendar/2017/rakudo}]


== エディタ

@<B>{藍}: 私は普段はvimとvscodeを使っているよ。vimはシンタックスハイライトも効くんだけど、 何故かRakuのシンタックスハイライトだけ重いからRakuのプログラムだけはシンタックスハイライトを切ってるよ。
IDEでプログラミングしたい人はCommaIDE@<fn>{comma_ide}がおすすめだよ。
CommaはRakuやMoarVMのメイン開発者たちが開発に関わっているから信頼のおけるIDEなんだ。


//footnote[comma_ide][@<href>{https://commaide.com/}]
