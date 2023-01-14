/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=11", "Hack Bold Nerd Font:size=11" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=14";
static const char norm_fg[] = "#D3C6AA";
static const char norm_bg[] = "#232A2E";
static const char norm_border[] = "#232A2E";
static const char unsel_border[] = "#232A2E";

static const char sel_fg[] = "#A7C080";
static const char sel_bg[] = "#A7C080";
static const char sel_fg1[] = "#A7C080";
static const char sel_bg1[] = "#232A2E";
static const char sel_border[] = "#24283b";
static const char dsel_bg[] = "#232A2E";
static const char for_border[] = "#A7C080";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg,     norm_bg,   unsel_border }, // unfocused wins
    [SchemeSel]  = { sel_fg1,      sel_bg1,    for_border },  // the focused win
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
// static const char *tags[] = {"", "", "", "", "", ""};
static const char *tags[] = {"", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define ALTKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", sel_bg, "-sb", norm_bg, "-sf", norm_fg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,             			XK_d,      spawn,          SHCMD("rofi -modi drun -show drun -config ~/.config/rofi/rofidmenu.rasi") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ ALTKEY,             			XK_Return, spawn,          SHCMD("kitty") },
	{ ALTKEY|ShiftMask,             XK_Return, spawn,          SHCMD("alacritty") },
	{ MODKEY,             			XK_b,      spawn,      	   SHCMD("firefox") },
	{ MODKEY,             			XK_e,      spawn,      	   SHCMD("thunar") },
	{ MODKEY|ALTKEY,             	XK_e,      spawn,      	   SHCMD("externalmonitor") },
	{ MODKEY,             			XK_w,      spawn,      	   SHCMD("brave") },
	{ MODKEY|ALTKEY,			    XK_x, 	   spawn,          SHCMD("systemctl poweroff") },
	{ MODKEY,			    		XK_x, 	   spawn,          SHCMD("powermenudwm") },
	{ MODKEY|ALTKEY,      			XK_r, 	   spawn,          SHCMD("systemctl reboot") },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
	{ ALTKEY,             			XK_w,      spawn,      	   SHCMD("feh --randomize --bg-scale ~/.wallpapers/widescreen") },
	{ MODKEY|ALTKEY,             	XK_w,      spawn,      	   SHCMD("feh --randomize --bg-scale ~/.wallpapers/everforest") },
	{ ALTKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ ALTKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ ALTKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ALTKEY,              	XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY,              	XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|ALTKEY|ControlMask,  	XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ControlMask,  	XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_0,      togglegaps,     {0} },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY,              	XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("amixer set Master toggle") },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("amixer set Master 5%-") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("amixer set Master 5%+") },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

