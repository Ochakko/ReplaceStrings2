export set EF_DISABLE_BANNER=0
#デフォルトでは efenceを導入すると、“Electric Fence 2.1 Copyright (C) 1987-1998 Bruce Perens.”
#とかいうバナーが表示されるんだけど、これを1にしておくと出なくなる。どうでもいい気もするけどテストとかで重要なのかな。

export set EF_ALIGNMENT=1
#このサイズ未満オーバーは検出しない。0, 1にすると全てチェック。デフォルトはマシンのintサイズ。そうなっているのはfalse positive抑制のため。

export set EF_PROTECT_BELOW=0
#1でアンダーラン検出。当たり前だけどオーバーアンダー同時チェックはできない。

export set EF_ALLOW_MALLOC_0=1
#0サイズのmallocを許す。

export set EF_PROTECT_FREE=1
#1にするとfree()したところを再利用しなくなる。
#デフォルトではmallocで再利用されると不正アクセスがチェックされなくなるので、「あやしい」と思ったらつけておくと良い。

export set EF_FREE_WIPES=1
#1にするとfree()したところを0xbdで上書きしてくれる。


