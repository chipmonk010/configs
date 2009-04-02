/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-monofur-medium-r-normal-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#cccccc";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#a6a6a6";
static const char selbordercolor[]  = "#222222";
static const char selbgcolor[]      = "#222222";
static const char selfgcolor[]      = "#a6a6a6";
static unsigned int borderpx        = 1;        /* border pixel of windows */
static unsigned int snap            = 8;       /* snap pixel */
static Bool showbar                 = True;     /* False means no bar */
static Bool topbar                  = True;     /* False means bottom bar */
static Bool usegrab                 = False;    /* True means grabbing the X server
                                                   during mouse-based resizals */

/* tagging */
static const char tags[][MAXTAGLEN] = { "TERM","TERM", "WWW", "MAIL", "MEDIA", "MISC" };
static unsigned int tagset[] = {1, 1}; /* after start, first tag is selected */

static Rule rules[] = {
	/* class				instance    title       tags mask     isfloating */
	{ "Gimp",					NULL,       NULL,       0,            True },
	{ "Firefox",			NULL,       NULL,       1 << 2,       False },
	{ "Thunderbird",	NULL,       NULL,       1 << 3,       False },
	{ "MPlayer",			NULL,       NULL,       0,						True },
};

/* layout(s) */
static float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static Bool resizehints = False; /* False means respect size hints in tiled resizals */

/* custom functions declarations */
static void bstack(void);
static void cyclelayout(const Arg *arg);
static void kbmvresize(const Arg *arg);

static Layout layouts[] = {
	/* symbol     arrange function */
	{ "oO_",      tile },    /* first entry is default */
	{ "TTT",			bstack },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "xterm", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *emailcmd[]  = { "thunderbird", NULL };
static const char *runcmd[]  = { "gmrun", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_Left,   kbmvresize,     {.v = (int []){ -40, 0, 0, 0 } } },
  { MODKEY,                       XK_Up,     kbmvresize,     {.v = (int []){ 0, -40, 0, 0 } } },
  { MODKEY,                       XK_Right,  kbmvresize,     {.v = (int []){ 40, 0, 0, 0 } } },
  { MODKEY,                       XK_Down,   kbmvresize,     {.v = (int []){ 0, 40, 0, 0 } } },
  { MODKEY|ShiftMask,             XK_Left,   kbmvresize,     {.v = (int []){ 0, 0, -40, 0 } } },
  { MODKEY|ShiftMask,             XK_Up,     kbmvresize,     {.v = (int []){ 0, 0, 0, -40 } } },
  { MODKEY|ShiftMask,             XK_Right,  kbmvresize,     {.v = (int []){ 0, 0, 40, 0 } } },
  { MODKEY|ShiftMask,             XK_Down,   kbmvresize,     {.v = (int []){ 0, 0, 0, 40 } } },
	{ MODKEY,                       XK_r,      spawn,          {.v = runcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emailcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  cyclelayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* custom functions */

void bstack(void) {
	int x, y, h, w, mh;
	unsigned int i, n;
	Client *c;

	for(n = 0, c = nexttiled(clients); c; c = nexttiled(c->next), n++);
	if(n == 0) {return;}

	c = nexttiled(clients);
	mh = mfact * wh;
	adjustborder(c, n == 1 ? 0 : borderpx);
	resize(c, wx, wy, ww - 2 * c->bw, (n == 1 ? wh : mh) - 2 * c->bw, resizehints);

	if(--n == 0) {return;}

	x = wx;
	y = (wy + mh > c->y + c->h) ? c->y + c->h + 2 * c->bw : wy + mh;
	w = ww / n;
	h = (wy + mh > c->y + c->h) ? wy + wh - y : wh - mh;
	if(h < bh) {h = wh;}

	for(i = 0, c = nexttiled(c->next); c; c = nexttiled(c->next), i++) {
		adjustborder(c, borderpx);
		resize(c, x, y, ((i + 1 == n) ? wx + ww - x : w) - 2 * c->bw,
					 h - 2 * c->bw, resizehints);
		if(w != ww) {x = c->x + WIDTH(c);}
	}
}

void cyclelayout(const Arg *arg) {
	lt[sellt]++; 
	if (lt[sellt] == layouts + LENGTH(layouts)) { lt[sellt] = layouts;}
  if(sel) { arrange();}
  else { drawbar();}
}

static void kbmvresize(const Arg *arg) {
  if(!sel || (lt[sellt]->arrange && !sel->isfloating))
    return;

  resize(sel, sel->x + ((int *)arg->v)[0],
              sel->y + ((int *)arg->v)[1],
              sel->w + ((int *)arg->v)[2],
              sel->h + ((int *)arg->v)[3], True);
}

