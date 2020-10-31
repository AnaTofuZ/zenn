= Rakuの環境構築

//abstract{
Rakuの知識が深まったところで、著者の環境であるmacOSを中心に、 Rakuの言語の環境構築をしていきます。
//}

== Rakuのインストール

@<B>{藍}: RakuはMoarVM + NQP + Rakudoの3点セットをインストールしないと使えないんだ。でも、 このRaku関連のパッケージを一つにまとめた@<B>{Rakudo Star}というパッケージが便利だよ。
macOSならhomebrewでインストールすることが可能かな。


=== rakudobrew

//terminal[raku_install][RakudoStarのインストール(mac os)]{
$ brew install rakudostar
//}

ただRakudoStarは更新頻度が季節ごとだから、 当時の最新リリースが入っている訳じゃないんだ。 @<br>{}

@<B>{橙}: RakuはPerl5みたいに、5.28.0 みたいなバージョンじゃないんですか? @<br>{}

@<B>{藍}: Rakuの仕様で6.d や 6.f のようなバージョンは存在するよ。 これはプログラムから@<code>{use 6.d;}のような形で動きを指定できるんだ。
それとは別にRakudoはGitHubでバージョンが定期的にリリースされているんだ。 大体年月日がそのままバージョンになっているかな。 @<br>{}

@<B>{橙}: RakudoStar自体のバージョンみたいなのは存在しないんですか? @<br>{}

@<B>{藍}: 実は存在しているよ。 でもhomebrewでインストールできるRakudoStarは更新がされていなくて、 公式サイト@<fn>{rakudo_web_site}からdmgでダウンロードしないといけないんだ。 @<br>{}


=== バージョンごとのインストール

@<B>{藍}: rakudo-starはたしかに便利だけど、最新のrakudoを使いたい人や、 いくつかのバージョンのrakudoを同時に動かしたい人のはちょっと不便だよね。
各バージョンごとにインストールや切り替えができるツールとして、 @<B>{rakudobrew}@<fn>{rakudobrew}や@<B>{p6env}@<fn>{p6env}などが存在するよ。 
2020/02/14現在でrakudoの最新のバージョンは@<b>{2020.01}なんだけど、 これはhomebrewのRakudoStarではいれることは出来ない。
でも、 rakudobrewやp6envではインストール可能だよ。私としてもrakudobrewかp6envを使うのがおすすめかな。  @<br>{}

//footnote[rakudobrew][@<href>{https://github.com/tadzik/rakudobrew}]
//footnote[p6env][@<href>{https://github.com/skaji/p6env}]
//footnote[rakudo_web_site][@<href>{https://rakudo.org/star}]

=== p6env

@<B>{藍}: rakudobrew以外にp6envでのインストール方法を見てみよう。 PerlやRubyでplenvやrbenvを使っている人はだいたい使い勝手は同じだよ。 @<br>{}

@<B>{橙}: わたしが普段使っているのはzshだから、 zsh上でのインストールを試してみます。まずはp6envをgithubからgit cloneします。
p6envでは、 rakuのビルドに @<B>{perl6-build}@<fn>{perl6-build}が別途必要みたいなので、 これも同時にcloneします! 
clone先は特に問題がなさそうなので、ホームディレクトリの@<strong>{.p6env}以下にします。

//terminal[p6env_clone][p6envのクローン]{
$ git clone https://github.com/skaji/p6env ~/.p6env
$ git clone https://github.com/skaji/perl6-build ~/.p6env/plugins/perl6-build
//}

@<b>{橙}: 次にシェルのechoを使って、 zshの設定ファイルのzshrcに設定を書き加えます。
具体的にはPATHの指定と、シェル起動時にp6envを初期化するp6env initを実行する様に書き加えます! @<br>{}

@<b>{藍}: もじbashを使っている人がいれば、 zshrcの代わりにbash_profileなどにすればいいですよ!!

//terminal[p6env_add_zsh][p6envの設定をzshrcに書き加える]{
$ echo 'export PATH="$HOME/.p6env/bin:$PATH"' >> ~/.zshrc
$ echo 'eval "$(p6env init -)"' >> ~/.zshrc
//}

@<b>{橙}: 設定ファイルの再読み込みでも大丈夫そうですが、 念の為にシェルを再起動します。

//terminal[p6env_exec_shell][シェルの再起動]{
$ exec $SHELL -l
//}


@<B>{橙}: ここまで出来たらp6envが使える様になっているはずです。 念の為にhelpオプションを付けて実行してみます!

//terminal[p6env_help][p6envのhelpオプション]{
$ p6env --help
Usage: p6env <command> [<args>]

Some useful p6env commands are:
   commands      List all available p6env commands
   local         Set or show the local application-specific Perl6 version
   global        Set or show the global Perl6 version
   shell         Set or show the shell-specific Perl6 version
   install       Install a Perl6 version using perl6-build
   uninstall     Uninstall a Perl6 version
   rehash        Rehash p6env shims (run this after installing executables)
   version       Show the current Perl6 version and its origin
   versions      List all Perl6 versions available to p6env
   which         Display the full path to an executable
   whence        List all Perl6 versions that contain the given executable
   install-zef   Install zef from git repository

See `p6env help <command>' for information on a specific command.
For full documentation, see: https://github.com/skaji/p6env#readme
//}

@<B>{藍}: すでにrbenvやplenvを使っている人にはおなじみのサブコマンドが並んでいるね。 
とりあえず最新バージョンのrakudoをインストールしてみよう。 
まずはp6envでインストールできるバージョンの一覧を確認するよ。

//terminal[p6env_install_l][p6envでインストールできるバージョンの一覧]{
$ p6env install -l      # install できるversion のリスト
Available versions (latest 20 versions):
 rakudo-star-2020.01
 rakudo-star-2019.03
 rakudo-star-2018.10
 rakudo-star-2018.06
 rakudo-star-2018.04
 rakudo-star-2018.01
 rakudo-star-2017.10
 rakudo-star-2017.07
 rakudo-star-2017.04
 rakudo-star-2017.01
 2020.02.1
 2020.02
 2020.01
 2019.11
 2019.07.1
 2019.07
 2019.03.1
 2019.03
 2018.12
 2018.11
//}

@<B>{藍}: ここではrakudo-starのいくつかのバージョンと、月ごとのリリースバージョンが一覧で取れるね。 
最新版である2020.02.1をインストールしてみるよ。

//terminal[p6env_install][p6envを使ったinstall]{
$ p6env install 2020.02.1
Updating https://github.com/rakudo/rakudo
Updating https://github.com/MoarVM/MoarVM
Updating https://github.com/perl6/nqp
Running /Users/anatofuz/.plenv/versions/5.28.1/bin/perl5.28.1 Configure.pl --prefix /Users/anatofuz/.p6env/versions/2020.02.1 --make-install --git-reference /Users/anatofuz/.p6env/git_reference --backends moar --gen-moar

  See /Users/anatofuz/.p6env/build/1583480425.2081/build.log for progress

Done
//}

@<B>{橙}: しっかりMoarVM, NQP, Rakudoの3つがインストールされていますね!! 
Doneと出たので完了したはずなので、p6envの機能を使って、 普段使いのrakuを今インストールしたバージョンに切り替えてみます。
p6envは@<code>{global}サブコマンドでバージョンを指定すると、 環境のすべてのrakuやperl6, nqpコマンドが、任意のバージョンに切り替わります。

//terminal[p6env_mod_version1][p6envでグローバルに環境を切り替え]{
$ p6env global 2020.02.1  # global 環境の切り替え
//}

@<B>{藍}: しっかり切り替わっているか、実際にrakuのコマンドから確認してみよう。
ちなみにp6envを使ってビルドすると、perl6コマンドの他にも@<B>{raku}や@<B>{rakudo}コマンドが使えるようになるんだ。
これらは内容はperl6コマンドと同一だけど、 Rakuを書いてるっぽくなるので、 好きな人はこれを使ってみよう。
もちろん、今まで通りperl6コマンドでも可能だよ。 @<code>{--version}オプションをつけるとバージョンが確認できるんだ。

//terminal[p6env_version_check][今動いているrakuのバージョンを確認する]{
$ raku --version
This is Rakudo version 2020.02.1 built on MoarVM version 2020.02.1
implementing Raku 6.d.
//}

@<B>{藍}: 無事インストール出来たようだね。次にRakuでライブラリのインストールに利用する@<strong>{zef}もインストールしてみよう。

//terminal[p6env_mod_version2][p6envを使ったinstall]{
$ p6env install-zef     # ライブラリインストーラーのzefのインストール
Updating https://github.com/ugexe/zef
Already up to date.
===> Testing: zef:ver<0.8.3>:auth<github:ugexe>:api<0>
===> Testing [OK] for zef:ver<0.8.3>:auth<github:ugexe>:api<0>
===> Installing: zef:ver<0.8.3>:auth<github:ugexe>:api<0>

1 bin/ script [zef] installed to:
/Users/anatofuz/.p6env/versions/2020.02.1/share/perl6/site/bin
//}

@<B>{橙}: 無事インストールできました!! 試しにRakuのREPLを強化するLinenoiseモジュールを入れてみます。

//terminal[p6env_mod_version3][zefでLinenoiseモジュールのインストール]{
$ zef install Linenoise
===> Searching for: Linenoise
===> Updating p6c mirror: https://raw.githubusercontent.com/ugexe/Perl6-ecosystems/master/p6c1.json
===> Updating cpan mirror: https://raw.githubusercontent.com/ugexe/Perl6-ecosystems/master/cpan1.json
===> Updated p6c mirror: https://raw.githubusercontent.com/ugexe/Perl6-ecosystems/master/p6c1.json
===> Updated cpan mirror: https://raw.githubusercontent.com/ugexe/Perl6-ecosystems/master/cpan1.json
===> Searching for missing dependencies: LibraryMake
===> Searching for missing dependencies: Shell::Command
===> Searching for missing dependencies: File::Which, File::Find
===> Building: Linenoise:ver<0.1.1>:auth<Rob Hoelz>
===> Building [OK] for Linenoise:ver<0.1.1>:auth<Rob Hoelz>
===> Testing: File::Which:ver<1.0.1>
[File::Which] # Found perl6 at '/Users/anatofuz/.p6env/versions/2020.02.1/bin/perl6'
[File::Which] # Found perl6 at '/Users/anatofuz/.p6env/versions/2020.02.1/bin/perl6' using whence
===> Testing [OK] for File::Which:ver<1.0.1>
===> Testing: File::Find:ver<0.1>
===> Testing [OK] for File::Find:ver<0.1>
===> Testing: Shell::Command
===> Testing [OK] for Shell::Command
===> Testing: LibraryMake:ver<1.0.0>:auth<github:retupmoca>
===> Testing [OK] for LibraryMake:ver<1.0.0>:auth<github:retupmoca>
===> Testing: Linenoise:ver<0.1.1>:auth<Rob Hoelz>
===> Testing [OK] for Linenoise:ver<0.1.1>:auth<Rob Hoelz>
===> Installing: File::Which:ver<1.0.1>
===> Installing: File::Find:ver<0.1>
===> Installing: Shell::Command
===> Installing: LibraryMake:ver<1.0.0>:auth<github:retupmoca>
===> Installing: Linenoise:ver<0.1.1>:auth<Rob Hoelz>
//}

@<B>{藍}: 無事にこっちの方もインストールできたみたいだね!! 

//footnote[perl6-build][@<href>{https://github.com/skaji/perl6-build}]

=== ソースコードからのビルド

@<B>{橙}: ソースコードをcloneしてきてビルドしたいときはどうすればいいんですか? @<br>{}

@<B>{藍}: 公式のREADMEのbuild関連の記述@<fn>{rakudo_github_readme_build}の通りにするのがいいかな。
RakudoはビルドスクリプトがPerl5で記述されているから、 Perlスクリプトを実行するとビルドできるよ。

//terminal[raku_build_from_src][Rakudoのインストール]{
$ git clone https://github.com/rakudo/rakudo.git
$ perl Configure.pl --gen-moar --gen-nqp --backends=moar
//}

@<B>{藍}: READMEの記述では、オプションとして@<code>{--gen-moar}や@<code>{--gen-nqp}を指定しているよ。
これはRakudoのビルド時に同時にMoarVMとNQPをビルドすることができるオプションなんだ。 
#@# Rakuプログラミングをする上で、NQPやMoarVMの知識が必要になるケースはあるかもしれないけど、 このオプションがあるから、ビルドする際に必要なコードはRakudoのコードだけで済むんだ。
RakudoはMoarVM上で動く上に、 Rakudo自体はNQPで書かれている都合上、 MoarVMとNQPをそれぞれビルドしなければならないんだ。
でも、このオプションがあるから、ビルドする際に必要なコードはRakudoのコードだけで済むんだ。
MoarVMやNQPはPerl5のスクリプトの中で、 自動でダウンロードされてビルドされていくよ。 @<br>{}

@<B>{橙}: 最後の @<code>{--backends=moar}ってなんですか? @<br>{}

@<B>{藍}: これはRakudoコンパイラが実行されるVMのことだよ。 
RakudoはJVMやJSでも動作するから、 他には@<b>{jvm}, @<b>{js}が選択可能だよ。
とはいえ現在開発が主に進められているのはMoarVMだから、 なにかJVMで動かさないと行けない事情がある以外はmoarでいいと思うよ。 @<br>{}

@<B>{橙}: ちなみに、 環境構築せずに手軽に試す方法とかはあるんですか? @<br>{}

@<B>{藍}: javacriptで実装されたRakuを試すなら、@<B>{6pad}というwebサイトがあるよ。
アクセスするだけで簡単に試す事もできるし、 cloneして手元で試すこともできるんだ。 @<br>{}

@<B>{橙}: 結構色々揃ってるんですね! すごい!! @<br>{}

@<B>{藍}: ちゃんとした処理系がほしいなら、 Dockerコンテナも用意してあるよ @<br>{}

//footnote[rakudo_github_readme_build][@<href>{https://github.com/rakudo/rakudo#configuring-rakudo-to-run-on-moarvm}]

== Rakuの実行


@<B>{橙}: ダウンロードしてみたのですぐRakuを使ってみたいです! @<br>{}

@<B>{藍}: RakuはPerl5と違って、 コマンドをそのまま実行するとインタプリタが起動するよ。 Pythonのpythonコマンドに似た挙動だね。
Rakuは今の所@<B>{perl6}か@<B>{raku}というコマンドで実行できるよ。@<fn>{raku_command_info}
//terminal[raku_interp_start][Rakuのインタプリタの起動(Perl6コマンドを使う場合)]{
$ perl6
To exit type 'exit' or '^D'
>
//}

//terminal[raku_interp_start2][Rakuのインタプリタの起動(Rakuコマンドを使う場合)]{
$ raku
To exit type 'exit' or '^D'
>
//}

@<B>{藍}: 試しにHello, World! でもしてみようかな。 Rakuで文字列出力は@<B>{say}を使うよ。 最後に自動的に改行が入る様になっているよ @<br>{}

//terminal[raku_interp_start][Rakuのインタプリタの起動]{
> say "Hello, World!"
Hello, World!
//}

@<B>{橙}: 無事世界にこんにちはできました!! 感動します!! @<br>{}

@<B>{藍}: さすがだね橙! それじゃぁ次はRakuのプログラミングについて勉強していこう!　 @<br>{}

//footnote[raku_command_info][今現在はperl6とrakuの両方が使用可能ですが、 そのうちperl6が非推奨になります。]
