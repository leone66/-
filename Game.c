#include "Game.h"
#include "GameLib.h"

#define SEP "------------------------------------------------------------------------------"
#define COL 78      //游戏界面总宽度
#define MARGIN_X 20 //左边距
#define MAP_START_Y 3   //地图的开始坐标
#define MAP_END_Y 11
#define INFO_START_Y 13
#define MAIN_MENU_START_Y 22

FILE * fp;
int X = 0, Y = 0;
int player_count = 2;
//英雄
Player players[100] = {
    {001, "乔弗里大帝", "123456789",  99, 0, 999999, 999999 ,5,8},
    {002, "韦赛里斯",   "123456abc",  1,  0, 100,    5      ,2,8},
};


Martial martials[] ={
    {1,  "王室"      , .hqCoord.X=7, .hqCoord.Y=3, 1, "维斯特洛大陆的统治者"},
    {2,  "坦格利安"  , .hqCoord.X=6, .hqCoord.Y=7, 1, "坦格利安家族的封地原先是黑水湾内的岛屿城堡龙石岛，在征服七大王国后坐镇七国首都君临城，统治维斯特洛近三百年之久。坦格利安家族的纹章是黑底红色的独身三头喷火龙，代表着“征服者“伊耿一世以及他的姐妹妻子维桑尼亚和雷妮丝。坦格利安家族的族语是“血火同源”，被俗称为“龙王”。"},
    {3,  "史塔克"    , .hqCoord.X=1, .hqCoord.Y=1, 1, "史塔克家族是北境最古老、最显赫也是最重要的家族，他们的历史可以追溯到“筑城者”布兰登——一名英雄纪元时期的传奇人物，他是临冬城的建立者，还和巨人族一起协助建立了绝境长城以防御异鬼的入侵。在“筑城者”布兰登之后长达几千年中，史塔克家族都是北境之王。在降服王托伦·史塔克向征服者伊耿投降后，北境成为坦格利安家族统治之下的七大王国之一，史塔克家族被封为北境守护，世袭此职。"},
    {4,  "兰尼斯特"  , .hqCoord.X=4, .hqCoord.Y=5, 1, "家族城堡为凯岩城，族徽是绯红地上的金色咆吼猛狮，族语为“听我怒吼”。此外，还有一句非正式的格言：“兰尼斯特有债必还。”这句话甚至比家族箴言更有名。兰尼斯特家族本有一把名为”光啸“的瓦雷利亚钢剑，但现在丢失了。兰尼斯特人以金发白肤，高大俊美为特征。"},
    {5,  "拜拉席恩"  , .hqCoord.X=6, .hqCoord.Y=2, 1, "七大家族最年轻的拜拉席恩家族诞生在征服战争时期，它的创立者是被谣传为伊耿的私生子弟弟的奥里斯·拜拉席恩。奥里斯·拜拉席恩由于战功显赫，不断被提拔，成长为了伊耿的干将之一。当奥里斯在征服战争期间击败并杀死最后一任风暴王“自大的”亚尔吉拉。奥里斯·拜拉席恩娶了亚尔吉拉的女儿，并继承了风暴王的家徽、族语，成为了第一任风息堡公爵。拜拉席恩家族的家徽是一只奔驰的带着王冠的黑鹿，族语是怒火燎原"},
    {6,  "徒利"      , .hqCoord.X=3, .hqCoord.Y=3, 1, "奔流城的徒利家族是河间地的首要家族，也是三叉戟河流域的统治者。家堡为奔流城。其族史可以追溯到英雄纪元的奔流城领主们，但他们从未称王。他们的家徽是腾跃于红蓝条纹底上的银色鳟鱼，家族箴言则是“家族，责任，荣誉。”"},
    {7,  "提利尔"    , .hqCoord.X=5, .hqCoord.Y=0, 1, "。提利尔家族庞大而富有，富裕程度仅次于兰尼斯特家族，但能动员出更强的军事力量。此外，如果提利尔家族征召手下封臣雷德温家族和盾牌列岛的舰队，加上海岸其他效忠家族的海军，那么提利尔家族能拥有的的海上军事力量不输于皇家舰队。在七大王国中，提利尔是个历史悠久，而崇尚骑士精神的家族，他们常以'边疆守护'和'河湾地至高统领'自封。家族族徽是一朵盛开于青翠绿野之上的金玫瑰；箴言为：生生不息。"},
    {8,  "艾林"      , .hqCoord.X=3, .hqCoord.Y=2, 1, "鹰巢城的艾林家族是谷地最重要的家族。艾林家族的封城为鹰巢城，此外他们也有许多其他城堡。他们的标志是天蓝色底色上，一只在白色月亮之上翱翔的天蓝色的鹰。他们的族语是“高如荣耀”。"},
    {9, "马泰尔"    , .hqCoord.X=6, .hqCoord.Y=1, 1, "“纳梅洛斯”意为“娜梅莉亚的血脉”，阳戟城是他们的统治中心。通常简称他们为马泰尔家族。马泰尔家族的家徽是一柄贯穿红日的金枪，金枪是古代马泰尔的家徽，红日象征洛伊拿，家族箴言是“不屈不挠”。马泰尔族人的外貌是典型的盐人，带有明显的洛伊拿人特征，他们有橄榄色的皮肤，黑眼黑发，不过少数家族成员则有棕土色的头发。"},
    {10, "葛雷乔伊"  , .hqCoord.X=3, .hqCoord.Y=4, 1, "铁群岛位于维斯特洛大陆西面，环境严酷，地形峻峭。其家族世代以海盗抢夺为生且以此为荣，家族的纹章是一只黑色底衬的金色海怪，族语为：强取胜于苦耕。"},
    {11, "守夜人"    , .hqCoord.X=0, .hqCoord.Y=0, 1, "守夜人是一个专门守卫绝境长城的军团。绝境长城是位于七大王国北方边境用来保卫王国居民的巨大的城墙。军团建立于英雄纪元时期异鬼入侵被击退之后。守夜人只穿着黑衣。"},
    {12, "异鬼"      , .hqCoord.X=0, .hqCoord.Y=6, 1, "传说中，8000年在持续时间长达一个世代的凛冬，那个被称作长夜的漫长黑暗时代里，异鬼第一次降临人间。最终，它们被人类和森林之子联合击退，随后绝境长城被建立起来抵御异鬼。而一个显而易见的矛盾事实是，传说中夜王娶了一位像异鬼一样的女人，但当他被击败后，异鬼就此销声匿迹，在长城以南逐渐变为了用来吓唬小孩子的纯粹的神话故事。但是维斯特洛人在互相咒骂时仍会用异鬼作为口头语。"}
};

Monster monsterArray[] = {
    {1,  "小偷",       1, 60,  3,   8,   8,   10,  10,   1, {4, 4}},
    {2,  "强盗",       2, 100, 5,   12,  10,  18,  30,   1, {4, 4}},
    {3,  "强奸犯",     3, 150, 6,   15,  15,  20,  50,   1, {4, 4}},
    {4,  "卫兵",       3, 230, 7,   20,  25,  35,  100,  1, {0, 0}},
    {5,  "记事本",     3, 300, 9,   28,  40,  50,  200,  1, {0, 0}},
    {6,  "野人",       4, 350, 10,  30,  55,  70,  500,  1, {4, 0}},
    {7,  "野生冰原狼", 4, 400, 12,  40,  60,  75,  800,  1, {1, 1}},
    {8,  "守夜人叛徒", 3, 300, 18,  45,  65,  85,  1000, 1, {4, 0}},
    {9,  "尸鬼",       5, 500, 30,  80,  70,  90,  1200, 1, {1,0}},
    {10, "无名异鬼",   5, 500, 40,  100, 75,  100, 1500, 1, {2,0}},
    {11, "堕落骑士",   8, 800, 60,  120, 80,  120, 1800, 1, {5,2}},
    {12, "善主",       7, 700, 70,  180, 80,  130, 2000, 1, {1,7}},
    {13, "贤主",       7, 700, 85,  180, 80,  130, 2500, 1, {2,7}},
    {14, "夜王",       9, 900, 100, 230, 100, 150, 4000, 1, {6,0}},
    {15, "黑龙",       9, 900, 150, 200, 150, 200, 6000, 1, {6,0}},
};

Map mapArray[8][8] ={
    {
        {1, "黑城堡",   1, {0, 0}, "守夜人的主要堡垒，位于王后门以东，橡木盾以西，靠近长城中心，在国王大道北方的尽头。"},
        {2, "先民拳峰", 1, {1, 0}, "黎明纪元时期先民所修筑的环堡。它的位置在乳河边。这里是守夜人的先民拳峰之战发生的地方。"},
        {3, "霜雪之牙", 1, {2, 0}, "霜雪之牙坐落于影子塔和先民拳峰的东北方。它是被守夜人称为叉梢的两座高峰之一。"},
        {4, "风声峡",   1, {3, 0}, "位于塞外通往霜雪之牙的一条通道。得名是因为狂风穿过峡口，发出的如哭嚎般的声音。"},
        {5, "卡斯特堡", 1, {4, 0}, "并不是一个真正意义上的堡垒，所谓堡垒只不过是守夜人给取的名字。坐落在长城以北。他的主人是卡斯特，一个坏脾气的野人，同时也是守夜人的朋友。"},
        {6, "布兰馈赠", 1, {5, 0}, "是绝境长城向南25里格的土地。这片土地由“筑城者”布兰，或其他某个名为布兰登·史塔克的北境之王赠送给守夜人。"},
        {7, "绝境长城", 1, {6, 0}, "坐落于七大王国极北地带、由冰雪筑成的巨大的防御工事，其将王国与野人的土地分割开来。它从最西端的霜雪之牙山脉，一直延伸至最东端的海豹湾。"},
        {8, "海豹湾",   1, {7, 0}, "北境一个海湾。它位于长城以东，一直延伸到东南面的安柏家族领地。守夜人的城堡东海望就坐落在海豹湾岸边。斯卡格斯岛亦位于其中。"}
    },
    {
        {9,  "最后壁炉", 1, {0, 1}, "安柏家族的家堡，其位置靠近新赠地紧挨末江。它在长湖的东北、海豹湾的西边、国王大道的东边。除了守夜人的堡垒，最后的壁炉城就是七大王国最北的城堡了。"},
        {10, "临冬城",   1, {1, 1}, "史塔克家族祖传的城堡和权力的中心，被认为是北境的首府。其坐落于七大王国北方省份的中心，国王大道将其与君临和长城连接起来。"},
        {11, "卡霍城",   1, {2, 1}, "北境卡史塔克家族的家堡，是一座坚固的堡垒，位于北境的东部，海豹湾的南边，再往东是大峭壁。"},
        {12, "恐怖堡",   1, {3, 1}, "波顿家族的城堡。它位于大陆东侧，矗立于泪江岸。"},
        {13, "灰水望",   1, {4, 1}, "大概位于颈泽内部，卡林湾的西南方。灰水望没有学士，也没有骑士和武器师傅。有史以来，安达尔人、铁民、佛雷家族和其他所有试图征服灰水望的军队，连找都找不到它。"},
        {14, "深林堡",   1, {5, 1}, "葛洛佛家族的居地。位于海龙角北方，狼林深处。它是山丘上的一座木头堡垒。就席恩·葛雷乔伊来说，它“不过是荒山上的木尿壶”。"},
        {15, "公羊门",   1, {6, 1}, "是北境的一座要塞，位于断肢河入海口，寡妇望的西边。"},
        {16, "托伦方城", 1, {7, 1}, "陶哈家族的居城，位于临冬城的西南方的大湖边。它的城墙乃是石砌，三十尺高，四角各有一座方塔，中央还有一座方形碉堡。这是个坚固的堡垒。"}


    },
    {
        {17, "老城",     1, {0, 2}, "洛克家族的居城，位于北境咬人湾沿岸。 "},
        {18, "寡妇望",   1, {1, 2}, "寡妇望的菲林特家族的领地。它坐落的位置几乎是维斯特洛大陆的最东边。也很靠近狭海的海岸。"},
        {19, "白港",     1, {2, 2}, "一个大港口城市，坐落于临冬城南方，是曼德勒家族的封地。白港是颈泽以北最大的居住地，但是维斯特洛五大城市中最小的。白港是北境主要的贸易港口，其位于白刃河河口，可以提供更多的贸易机会去更北的地区。"},
        {20, "霍伍德城", 1, {3, 2}, "位于北境的恐怖堡与白港之间，是霍伍德家族的家堡。"},
        {21, "卡林湾",   1, {4, 2}, "巨大沼地颈泽北端的一座废弃城堡。它是北境的一部分，属于史塔克家族的管辖，但是已经有几个世纪无人居住。卡林湾把守着能让军队安全通过颈泽的堤道，让它成为数千年来守卫北境，面对南方侵略的战略要地。"},
        {22, "荒冢屯",   1, {5, 2}, "有时也被称作荒冢镇，是北境的重要城镇，达斯丁家族的家堡荒冢厅也矗立于此。它坐落于先民荒冢上，接近两条向南流向盐矛滩的河流。！"},
        {23, "腾石镇",   1, {6, 2}, "是河湾地的傅德利家族的家堡"},
        {24, "暮谷镇",   1, {7, 2}, "其建于港口旁，道路由鹅卵石铺就，是莱克家族的领地。城北临一道白色悬崖，道路在海岸与石灰岩小山间延伸。渔村星罗棋布于绵延数里的路边。城南面的岩石半岛保护停泊的船只不受狭海上的风暴袭击。"}


    },
    {
        {25, "罗斯比城", 1, {0, 3}, "是罗斯比家族的家堡。位于君临北部，是君临到暮谷镇的捷径。罗斯比村镇不大，到处是木条泥土搭成的小屋。"},
        {26, "孪河城",   1, {1, 3}, "又称河渡口，是佛雷家族在渡河口处的要塞，位于河间地。要从北境到西河间地，此处是绿叉河上下几百里内唯一的渡河点，正好坐落在从临冬城到奔流城的大路上。"},
        {27, "鹰巢城",   1, {2, 3}, "安达尔人最古老的传人之一，自古以来的家堡。其耸立在明月山脉的顶端，横跨巨人之枪，谷地就坐落在几千英尺的下方。鹰巢城被认为是无法攻破的。"},
        {28, "奔流城",   1, {3, 3}, "徒利家族祖传几千年的家堡，在安达尔人入侵期间由亚赛尔·徒利大人建立。奔流城位于腾石河与红叉河相交之处。"},
        {29, "派克岛",   1, {4, 3}, "派克岛上有派克城和君王港。君王港是波特利家族的居地，离派克城最近的港口。派克岛离哈尔洛岛有一天的航程。"},
        {30, "赫伦堡",   1, {5, 3}, "它是一座建于征服战争之前的巨大城堡，位于河间地，在神眼湖北岸。是七大王国中最大的堡垒。但自从征服战争以来，这一直就是一个阴暗且满目疮痍的地方。"},
        {31, "金牙城",   1, {6, 3}, "西境的一处要塞，是莱佛德家族的家堡。它扼守着从河间地穿过山间直达西境的一条大道。通常情况下，想要进攻西境，就必须首先拿下金牙城。"},
        {32, "君临城",   1, {7, 3}, "七大王国的首都，位于维斯特洛东海岸，俯瞰黑水湾。是红堡和王国王座，铁王座的所在地。城市被城墙所环绕，城墙被都城守备队所驻守，或者称之为“金袍子”。君临也是七大王国的一个重要港口，地位仅次于旧镇。"},
    },
    {
        {33, "黑水湾",   1, {0, 4}, "是维斯特洛东侧的一片巨大的海湾。位于王领中黑水河汇入狭海之处，只有喉道将其与狭海隔开。七国都城君临就位于黑水湾河口。港湾内有一处独特的地标名为人鱼王之矛，其中水流急、水势大。"},
        {34, "御林",     1, {1, 4}, "是君临城南部横亘黑水湾的一片森林。"},
        {35, "龙石岛",   1, {2, 4}, "一个位于黑水湾出口处的岛屿，其城堡被雕刻成龙的形状。龙石岛原为从瓦雷利亚自由堡垒流亡而来的坦格利安家族的封地。"},
        {36, "红堡",     1, {3, 4}, "七大王国之国王的皇宫。坐落于七国首都君临的伊耿高丘之上。"},
        {37, "跳蚤窝",   1, {4, 4}, "君临的贫民窟。它是城中的一片低贱区域，小巷里有能搞到'褐汤'的小店。猪圈、马厩和皮匠铺散发出的臭味混杂在酒窖和妓院的气味里。"},
        {38, "凯岩城",   1, {5, 4}, "西境首府，兰尼斯特家族的统治所在。 凯岩城和字面上的意思一样，是在一块巨大的岩石上雕刻而成，修建在上面的城墙和其他建筑物使得城堡的防御能力更加强大。事实上，凯岩城从未陷落过。"},
        {39, "兰尼斯港", 1, {6, 4}, "第二大港口城市，坐落于日落之海沿岸，在凯岩城以西，河间大道、黄金大道和滨海大道交汇的地方。"},
        {40, "卡斯特梅", 1, {7, 4}, "位于峭岩城和塔贝克厅附近，拥有丰富的金矿。曾是西境封臣雷耶斯家族的封地。雷耶斯家族因为冒犯了兰尼斯特家族，而被泰兰尼斯特铲除。"}

    },
    {
        {41, "高庭",     1, {0, 5}, "是河湾地位于曼德河畔的城堡。在七国时代这里是园丁家族的居城，征服战争以后被赐给了提利尔家族。"},
        {42, "旧镇",     1, {1, 5}, "维斯特洛规模最大的港口，是五大城市之一，也是其中最古老的一座——早在安达尔人入侵前就已由先民建成。"},
        {43, "青亭岛",   1, {4, 5}, "是维斯特洛最西南边的一座岛屿，由雷德温家族统治。"},
        {44, "古橡城",   1, {3, 5}, "是奥克赫特家族的族堡，位于河湾地。其位置在河湾地西部，滨海大道的正中处，[2]滨海大道穿城而过通往高庭。"},
        {45, "金树城",   1, {5, 5}, "是罗宛家族的族堡，其位于河湾地。其位于红湖以东，高庭正北。"},
        {46, "曼德河",   1, {6, 5}, "是河湾地最大的河流。河水流量巨大，河面宽阔。苦桥就位于该河之上。"},
        {47, "岑树滩",   1, {7, 5}, "位于河湾地，紧挨着舟徙河。这里是岑佛德家族的领地，领地内主要包括三部分：岑树滩堡、岑树滩镇和岑树滩草场。"},
        {48, "盛夏厅",   1, {7, 5}, "曾是坦格利安家族的夏宫，这座城堡只有少许防御工事。"}
    },

    {
        {49, "星坠城",   1, {0, 6}, "它位于多恩、夏日之海岸边。那里有一座被称为白石剑塔的高塔。星坠城守卫着多恩的西部港湾。"},
        {50, "阳戟城",   1, {1, 6}, "马泰尔家族的城堡，多恩的首府。它位于绿血河以北，坐落于维斯特洛大陆的东南海岸，三面环海。多恩亲王的私人住所流水花园位于阳戟城以西三里格的海滩边，一条滨海道路将它们分开。"},
        {51, "风息堡",   1, {2, 6}, "七大王国中最坚固的城堡之一，是拜拉席恩家族的家座，而在其之前的几千年，是古老的风暴王的王位。城堡据说被编织在城墙内的咒语所保护，以防止魔法通过城墙。"},
        {52, "高庭",     1, {3, 6}, "河湾地位于曼德河畔的城堡。在七国时代这里是园丁家族的居城，征服战争以后被赐给了提利尔家族。"},
        {53, "塔斯岛",   1, {4, 6}, "维斯特洛沿岸的附属岛屿之一。它是塔斯家族的封地，他们的居城位于岛上的暮临厅。塔斯岛曾经是独立的王国，但现在被认为是风暴地的一部分。塔斯家族向风息堡效忠。"},
        {54, "盛夏群岛", 1, {5, 6}, "位于维斯特洛和厄斯索斯以南，索斯罗斯以西的海域的群岛。其西方是日落之海，东方是夏日之海。已知的世界地图中标注了盛夏群岛北方的三个大岛以及数个小岛，未知南方是否还有更多的岛屿。"},
        {55, "石阶列岛", 1, {6, 6}, "位于狭海中的一系列群岛，从多恩东部直达争议之地。石阶列岛是海盗们的巢穴。列岛中仅有两座岛有名字，血石岛和灰绞架岛。自由贸易城邦之一的泰洛西也位于石阶列岛中。"},
        {56, "千面屿",   1, {7, 6}, "千面屿是神眼湖中的一座小岛，是维斯特洛南部唯一生长着鱼梁木的地方。"}
    },
    {
        {57, "魁尔斯",   1, {0, 7}, "魁尔斯是已知世界中最大的港口之一，维斯·托罗若所缺乏的各种色彩似乎全跑到了魁尔斯。魁尔斯为自己的公会保留着单独的巨大码头。"},
        {58, "阿斯塔波", 1, {1, 7}, "奴隶湾的一座城市，坐落在蠕虫河河口。它以出产一种特殊的奴隶——无垢者而闻名。在丹妮莉丝到来之前，这里一直被善主统治着。"},
        {59, "渊凯",     1, {2, 7}, "奴隶湾东海岸的一座城市。其主要出口是奴隶，大多数都是性奴。这个城市的摇摇欲坠的城墙和高塔还有阶梯金字塔，全由黄色的砖块建成，被一群叫做贤主大人的奴隶主统治着。"},
        {60, "弥林",     1, {3, 7}, "奴隶湾的一处城邦，坐落于海湾的最北边，矗立于斯卡札丹河畔。它因奴隶贸易而闻名。"},
        {61, "多斯拉克", 1, {4, 7}, "厄斯索斯大陆上的一个大草原，位于自由贸易城邦的东部，生活着游牧民族多斯拉克人。"},
        {62, "瓦兰提斯", 1, {5, 7}, "位于自由贸易城邦的东南角，争议之地东部，洛恩河的入海口，是距离瓦雷利亚最近的自由贸易城邦。"},
        {63, "瓦雷利亚", 1, {6, 7}, "一座覆灭已久的城市，也是一座令人惊叹的城市，它曾是名为瓦雷利亚自由堡垒帝国的都城。其毁灭是由名为瓦雷利亚末日浩劫的灾难性事件所导致的。坦格利安家族的发源地。"},
        {64, "亚夏",     1, {7, 7}, "位于已知世界的最东南方。它地处厄斯索斯大陆东南方的一块楔形地块的尖端，是玉海与藏红花海峡交界处一座港口城市。亚夏的东北部就是传说中被阴影笼罩、被称为阴影之地的区域。"}
    },
};

//背包
Prop propArray[10][25] = {
    {
        {1,    "匕首",        1,  1,  30,    Weapon, .minAttack = 0,    .maxAttack = 5,    "刺客必备" },
        {2,    "长剑",        1,  1,  50,    Weapon, .minAttack = 3,    .maxAttack = 4,    "维斯特洛大陆士兵用的普通长剑"},
        {3,    "亚拉克弯刀",  1,  1,  50,    Weapon, .minAttack = 1,    .maxAttack = 5,    "多斯拉克人广泛使用的武器"},
        {4,    "布拉佛斯剑",  1,  1,  60,    Weapon, .minAttack = 2,    .maxAttack = 4,    "多斯拉克人广泛使用的武器"},
        {5,    "战斧",        2,  1,  60,    Weapon, .minAttack = 3,    .maxAttack = 6,    "凶险的阔首斧，比手斧大，用于劈开护甲和盾牌"},
        {6,    "棍棒",        2,  1,  70,    Weapon, .minAttack = 3,    .maxAttack = 6,    "君临的都城守卫队装备" },
        {7,    "长弓",        3,  1,  80,    Weapon, .minAttack = 4,    .maxAttack = 7,    "足以将箭射出250码远，并穿透敌人板甲"},
        {8,    "十字弓",      5,  1,  100,   Weapon, .minAttack = 6,    .maxAttack = 8,    "乔大帝最爱的武器"},
        {9,    "密尔十字弓",  7,  1,  200,   Weapon, .minAttack = 8,    .maxAttack = 12,   "能一次射出三支弩箭"},
        {10,   "野人长矛",    1,  1,  50,    Weapon, .minAttack = 2,    .maxAttack = 5,    "塞外野人用的矛，制作简单但是杀伤力大"},
        {11,   "长枪",        2,  1,  80,    Weapon, .minAttack = 3,    .maxAttack = 6,    "加长的长矛，北方军队特有的标志性武器"},
        {12,   "流星锤",      3,  1,  200,   Weapon, .minAttack = 8,    .maxAttack = 12,   "连枷和链子锤的近亲，非强壮者无法驾驭"},
        {13,   "瓦雷利亚匕",  8,  1,  3000,  Weapon, .minAttack = 15,   .maxAttack = 18,   "极端稀罕，瓦雷利亚钢制成，锋利程度和硬度都举世罕见"},
        {14,   "龙骨弓",      8,  1,  500,   Weapon, .minAttack = 12,   .maxAttack = 15,   "龙骨弓因其射程远超过一般木弓而一弓难求，并得到多斯拉克人的高度评价"},
        {15,   "瓦雷利亚剑",  10, 1,  5000,  Weapon, .minAttack = 18,   .maxAttack = 20,   "极端稀罕，多数瓦雷利亚钢剑都拥有一段属于自己的传说，和极高的评价"},
        {16,   "加垫甲",      1,  1,  80,    Armor,  .minDefence = 50,  .maxDefence = 80,  "以皮革或帆布制作，通常用布料加以填充,被称为“软甲”"},
        {17,   "鳞甲",        2,  1,  150,   Armor,  .minDefence = 80,  .maxDefence = 100, "这种护甲的主体通常由帆布或者皮革等衣料制成，在面料内镶嵌有一列列长方形金属片"},
        {18,   "锁环铠",      3,  1,  300,   Armor,  .minDefence = 100, .maxDefence = 120, "这种护甲一环一环连接而成，它与环甲衫几乎是同一种东西"},
        {19,   "重装板甲",    4,  1,  500,   Armor,  .minDefence = 120, .maxDefence = 150, "武装到牙齿"},
        {20,   "秘银甲",      6,  1,  800,   Armor,  .minDefence = 200, .maxDefence = 250, "防御力世上少有,极其珍贵"},
        {21,   "龙晶",        5,  1,  500,   Con,    .minPower = 0,     .maxPower = 999,   "本质是黑曜石，森林之子用龙晶制作匕首、刀刃、箭头等武器，龙晶武器是异鬼为数不多的克星之一"},
        {22,   "夜影之水",    9,  1,  1000,  Con,    .minPower = 999,   .maxPower = 800,   "少量饮用可以忘记烦恼，饮用过量则会永久沉睡"},
        {23,   "里斯之泪",    10, 1,  1000,  Con,    .minPower = 999,   .maxPower = 1000,  "是一种非常罕见、价格高昂的毒药，它的味道清甜如水，可溶于酒中或是水中，嗅不出也尝不出"}
    },
    {
        {99,   "寡妇之嚎",    10, 50, 8000,  Weapon, .minAttack = 20,   .maxAttack = 25,   "乔大帝御用神剑,剑鞘由镀金樱桃木制成，由上过油的红皮革包裹，装饰着纯金狮子头"},
        {98,   "噬心",        9,  50, 8000,  Weapon, .minAttack = 16,   .maxAttack = 18,   "乔大帝御用神剑,剑柄上的圆球是一枚切割成心形的红宝石，嵌在狮口中，剑身有三道深深的血槽"},
        {8,    "十字弓",      5,  1,  30,    Weapon, .minAttack = 6,    .maxAttack = 8,    "乔大帝最爱的武器"},
        {999,  "天命之甲",    10, 50, 8000,  Armor,  .minDefence = 400, .maxDefence = 600, "取日月之精华合成的盾"},
        {1000, "猎狗",        8,  50, 10000, Con,    .minPower = 999,   .maxPower = 1000,  "乔大帝御用，他人使用必遭反噬"}
    },
    {
        {2,    "长剑",        1,  1,  50,    Weapon,  .minAttack = 3,   .maxAttack = 4,    "维斯特洛大陆士兵用的普通长剑"},
        {17,   "鳞甲",        2,  1,  150,   Armor,  .minDefence = 80,  .maxDefence = 100, "这种护甲的主体通常由帆布或者皮革等衣料制成，在面料内镶嵌有一列列长方形金属片"},
    }
};

Player *currPlayer;

//初始化
void Init()
{
    currPlayer = &players[0];
    players[0].martial = martials[0];
    players[0].weapon = propArray[1][0];
    players[0].armor = propArray[1][3];
    players[1].martial = martials[1];
    players[1].weapon = propArray[2][0];
    players[1].armor = propArray[2][1];
}

char * Star(char * password)
{
    int i = 0;
    while ((password[i] = getch()) != '\r')
    {
    if(password[i] != '\b')
    {
        putchar('*');
        i++;
    }
    else
    {
        printf("\b \b");
        i--;
    }
    }
    password[i] = '\0';
    return password;
}

void Show()
{
    int propCount = sizeof(propArray) / sizeof(Prop);
    int i;
    for(i = 0; i < propCount; i++)
    {
        printf("%d\t%s\t%d\n", currPlayer->weapon.id, currPlayer->weapon.name, currPlayer->weapon.price);
        switch(currPlayer->weapon.type)
        {
            case Weapon:
                printf("最小攻击力：%d\t最大攻击力：%d\n", currPlayer->weapon.minAttack, currPlayer->weapon.maxAttack);
                break;
            case Armor:
                printf("最小防御力：%d\t最大防御力：%d\n", currPlayer->weapon.minDefence, currPlayer->weapon.maxAttack);
                break;
            case Con:
                printf("最小能力值：%d\t最大能力值：%d\n", currPlayer->weapon.minPower, currPlayer->weapon.maxPower);
                break;
        }
    }
}

void ShowWelcome()
{
    SetPosition(MARGIN_X, 0);
    printf("%s\n", SEP);
    SetPosition(MARGIN_X, 1);
    printf("|");
    SetPosition(MARGIN_X + 30, 1);
    printf("Winter is coming!\n");
    SetPosition(MARGIN_X + 77, 1);
    printf("|");
    SetPosition(MARGIN_X, 2);
    printf("%s\n", SEP);

}

void ShowMapNC()
{
    int i;
    int j;
    for(i = 0; i < 8; i++)
    {
        SetPosition(MARGIN_X, MAP_START_Y + i);
        for(j = 0; j < 8; j++)
        {
            if (j == 0)
                printf("|   ");
            printf("%-9s", mapArray[i][j].name);
            SetColor(10, 0);
        }
        SetPosition(MARGIN_X + 77, 3 + i);
        printf("|");
        //printf("\n");
    }
    SetPosition(MARGIN_X, MAP_END_Y);
    printf(SEP);

}

void ShowMap()
{
    int i;
    int j;
    for(i = 0; i < 8; i++)
    {
        SetPosition(MARGIN_X, MAP_START_Y + i);
        for(j = 0; j < 8; j++)
        {
            if (j == 0)
                printf("|   ");
            if (i == Y && j == X)
            {
                //如果在当前位置，就更改地图颜色
                SetColor(5, 15);
            }
            printf("%-9s", mapArray[i][j].name);
            SetColor(10, 0);
        }
        SetPosition(MARGIN_X + 77, 3 + i);
        printf("|");
        //printf("\n");
    }
    SetPosition(MARGIN_X, MAP_END_Y);
    printf(SEP);
    ShowMapInfo();

}

void ShowMapInfo()
{
    //清除信息窗的信息
    //SetPosition(MARGIN_X + 5, INFO_START_Y + 1);

    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
    printf("当前玩家所在地图：%s", mapArray[Y][X].name);
    SetPosition(MARGIN_X + 10, INFO_START_Y);

    //控制字数
    char * desc = mapArray[Y][X].desc;
    int descLen = strlen(desc);
    int i;
    for(i = 0; i < descLen; i++)
    {
        if(i != 0 && i % 60 == 0)
        {
            SetPosition(MARGIN_X + 10, INFO_START_Y + i / 60);
        }
        printf("%c", desc[i]);
    }
    //printf("%s", mapArray[X][Y].desc);
}

void ShowInfo()
{
    int i;
    int j;
    for (i = 0; i < 9; i++)
    {
        for(j = 0; j < 7; j++)
        {
            SetPosition(MARGIN_X, INFO_START_Y + i - 1);
            printf("|");
        }
        printf("\n");
        SetPosition(MARGIN_X + 77, 12 + i);
        printf("|\n");
    }
    SetPosition(MARGIN_X, MAP_END_Y + 9);
    printf(SEP);

}

void ShowSquare()
{
    int i;
    int j;
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 7; j++)
        {
            SetPosition(MARGIN_X, MAIN_MENU_START_Y + i - 1);
            printf("|");
        }
        printf("\n");
        SetPosition(MARGIN_X + 77, MAIN_MENU_START_Y + i - 1);
        printf("|\n");
    }
    printf("\n");
    SetPosition(MARGIN_X, MAIN_MENU_START_Y + 6);
    printf(SEP);
}

void ShowWarn()
{
    SetPosition(MARGIN_X + 33, INFO_START_Y - 1);
    printf("健康游戏忠告");
    SetPosition(MARGIN_X + 1,  INFO_START_Y );
    printf("抵制不良游戏，拒绝盗版游戏。");
    SetPosition(MARGIN_X + 49,  INFO_START_Y );
    printf("注意自我保护，谨防受骗上当。");
    SetPosition(MARGIN_X + 1,  INFO_START_Y + 2 );
    printf("适度游戏益脑，沉迷游戏伤身。");
    SetPosition(MARGIN_X + 49,  INFO_START_Y + 2);
    printf("合理安排时间，享受健康生活。");
    SetPosition(MARGIN_X + 27,  INFO_START_Y + 4 );
    printf("本游戏拒绝16岁以下者访问！");
    SetPosition(MARGIN_X + 33,  INFO_START_Y + 5 );
    printf("按任意键继续...");
}
void showMainMenu()
{
    Clear(MARGIN_X + 1, MAIN_MENU_START_Y - 1, 7);
    SetPosition(MARGIN_X + 35, MAIN_MENU_START_Y - 1);
    printf("游戏菜单");
    SetPosition(MARGIN_X + 1,  MAIN_MENU_START_Y );
    printf("1.自我欣赏");
    SetPosition(MARGIN_X + 16, MAIN_MENU_START_Y );
    printf("2.查找怪物");
    SetPosition(MARGIN_X + 31, MAIN_MENU_START_Y );
    printf("3.回家");
    SetPosition(MARGIN_X + 46, MAIN_MENU_START_Y );
    printf("4.购买装备");
    SetPosition(MARGIN_X + 61, MAIN_MENU_START_Y );
    printf("5.切换装备");
    SetPosition(MARGIN_X + 1,  MAIN_MENU_START_Y + 2);
    printf("6.切换角色");
    SetPosition(MARGIN_X + 16, MAIN_MENU_START_Y + 2);
    printf("7.修改密码");
    SetPosition(MARGIN_X + 31, MAIN_MENU_START_Y + 2);
    printf("8.删除角色");
    SetPosition(MARGIN_X + 46, MAIN_MENU_START_Y + 2);
    printf("9.更改名称");
    SetPosition(MARGIN_X + 61, MAIN_MENU_START_Y + 2);
    printf("X.游戏存档");
}

void ProcessMainMenu(char key)
{
    switch(key)
    {
    case '1':
        ShowPlayerInfo();
        break;
    case '2':
        ShowMonsters();
        break;
    case '3':
        Move(currPlayer->martial.hqCoord.X, currPlayer->martial.hqCoord.Y);
        break;
    case '4':
        Trade();
        break;
    case '5':
        SwitchE();
        break;
    case '6':
        SwitchH();
        break;
    case '7':
        Repassword();
        break;
    case '8':
        DeleteH();
        break;
    case '9':
        Rename();
        break;
    case 'X':
        Save();
        break;
    }
}

void ShowPlayerInfo()
{
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
    printf("英雄<%s>的个人资料如下", currPlayer->name);
    SetPosition(MARGIN_X + 5, INFO_START_Y);
    printf("等级：%d\t血量：%d\t攻击：%d~%d\t防御：%d~%d", currPlayer->level, currPlayer->hp, currPlayer->level*2 + currPlayer->weapon.minAttack,
    currPlayer->level*2 + currPlayer->weapon.maxAttack,currPlayer->level + currPlayer->armor.minDefence,currPlayer->level + currPlayer->armor.maxDefence);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 1);
    printf("经验值：%d\t金币：%d\t\t\t所属势力：%s",currPlayer->exp,currPlayer->gold,currPlayer->martial.name);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 3);
    printf("当前武器：%s(攻击：%d~%d)\t当前防具：%s(防御：%d~%d)", currPlayer->weapon.name, currPlayer->weapon.minAttack,
    currPlayer->weapon.maxAttack, currPlayer->armor.name, currPlayer->armor.minDefence, currPlayer->armor.maxDefence);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 6);
    printf("按方向键返回");
}

void ShowMonsters()
{
    char *levelNames[] = {"初出茅庐", "粗通皮毛", "青年才俊", "略有小成", "心领神会", "无懈可击", "出类拔萃", "所向披靡", "天人合一"};
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    //SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
    //printf("当前地图<%s>的怪物如下", mapArray[Y][X].name);
    //怪物总数
    int monsterCount = sizeof(monsterArray) / sizeof(Monster);
    //当前地图的怪物下标数组
    int MonsterIndexs[9];
    //当前地图的怪物总数
    int currMapMonsterCount = 0;
    int i;
    for(i = 0; i < monsterCount; i++)
    {
        //查找当前地图的怪物总数
        if(monsterArray[i].coord.X == X && monsterArray[i].coord.Y == Y && monsterArray[i].state != 0)
        {
            MonsterIndexs[currMapMonsterCount] = i;
            currMapMonsterCount++;
            if(currMapMonsterCount == 9)
                break;
        }
    }
        //打印怪物
        SetPosition(MARGIN_X + 10, INFO_START_Y);
        if(currMapMonsterCount == 0)
        {
            printf("当前地图冷冷清清的");
            return;
        }
        SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
        printf("当前地图<%s>的怪物如下", mapArray[Y][X].name);
        SetPosition(MARGIN_X + 5, INFO_START_Y);
        for(i = 0; i < currMapMonsterCount; i++)
        {
            if(i != 0 && i % 3 == 0)
            {
                SetPosition(MARGIN_X + 5, INFO_START_Y + i / 3);
            }
            //int currIndex = MonsterIndexs[i]
            printf("%d.%s(%s)\t", monsterArray[MonsterIndexs[i]].id, monsterArray[MonsterIndexs[i]].name, levelNames[monsterArray[MonsterIndexs[i]].level - 1]);
        }

    /***************怪物PK*****************/
    //选择要打的怪物编号
    int PKMonsterId;
    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    printf("请输入要攻击的怪物(按\"0\"返回)：");
    scanf("%d", &PKMonsterId);
    if(PKMonsterId == 0)
    {
        ShowMap();
    }
    else
        {
            if(PKMonsterId < 16 && PKMonsterId > 0)
                {
                    Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
                    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
                    Fight(PKMonsterId);
                }
            else
                {
                    Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
                    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
                    printf("输入错误！");
                }
        }

}

void Fight(int monsterId)
{
    int monsterIndex = -1;  //查找的怪物下标
    int i = 0;
    for(i = 0; i < sizeof(monsterArray) / sizeof(Monster); i++)
    {
        if(monsterArray[i].id == monsterId)
        {
            monsterIndex = i;
            break;
        }
    }
    //没有找到
    if(monsterIndex == -1)
    {
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        printf("要对战的怪物不存在，请按任意键继续");
        return;
    }
    //如果怪物存在
    /*
    if(monsterIndex != -1) {
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        printf("已经锁定对战怪物，战斗即将开始");
        return;
    }
    */
    int fightCount = 0;
    while(1)
    {
            //开始打架
            srand(time(NULL));
            //玩家的攻击力
            //rand() % (b - a)
            int PlayerAttack = rand() % (currPlayer->weapon.maxAttack - currPlayer->weapon.minAttack) + 1 + currPlayer->weapon.minAttack;
            monsterArray[monsterIndex].hp -= PlayerAttack;
            if(monsterArray[monsterIndex].hp <= 0)
            {
                break;
            }
            currPlayer->hp -= monsterArray[monsterIndex].att;
            if(currPlayer->hp <= 0)
            {
                break;
            }
                SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
                Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
                SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
                fightCount++;
                printf("战斗第%d轮, %sHP:%d\t%sHP:%d", fightCount, currPlayer->name, currPlayer->hp, monsterArray[monsterIndex].name, monsterArray[monsterIndex].hp);
                usleep(1000 * 100);

    }

    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);

    if(currPlayer->hp <= 0)
        {
            SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
            printf("渡鸦来报：英雄<%s>在于怪物<%s>的战斗中壮烈牺牲", currPlayer->name, monsterArray[monsterIndex].name);
            currPlayer->hp = 100;
            return;
    }
    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    printf("渡鸦来报：<%s>被杀死，获得%d经验和%d金币(按方向键返回)", monsterArray[monsterIndex].name, monsterArray[monsterIndex].exp, monsterArray[monsterIndex].maxMoney);
    currPlayer->exp += monsterArray[monsterIndex].exp;
    currPlayer->gold += monsterArray[monsterIndex].maxMoney;
    if(currPlayer->exp >= currPlayer->level*100)
        {
            currPlayer->exp -= currPlayer->level*100;
            currPlayer->level++;
        }
    SetPosition(MARGIN_X + 5, INFO_START_Y + 5);

}

void Move(int x, int y)
{
    X = currPlayer ->martial.hqCoord.X;
    Y = currPlayer ->martial.hqCoord.Y;
    ShowMap();
}

void Trade()
{
    int i,j,k,n;
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 31, INFO_START_Y + -1);
    printf("欢迎光临布拉弗斯");
    for(i = 0;i < 25;i = i + 5)
    {
        SetPosition(MARGIN_X + 1 + 3*i,  INFO_START_Y);
        printf("%d.%s",propArray[0][i].id,propArray[0][i].name);
        if(propArray[0][i + 1].id != 0)
        {
            SetPosition(MARGIN_X + 1 + 3*i,  INFO_START_Y + 1);
            printf("%d.%s",propArray[0][i + 1].id,propArray[0][i + 1].name);
        }
        if(propArray[0][i + 2].id != 0)
        {
            SetPosition(MARGIN_X + 1 + 3*i,  INFO_START_Y + 2);
            printf("%d.%s",propArray[0][i + 2].id,propArray[0][i + 2].name);
        }
        if(propArray[0][i + 3].id != 0)
        {
            SetPosition(MARGIN_X + 1 + 3*i,  INFO_START_Y + 3);
            printf("%d.%s",propArray[0][i + 3].id,propArray[0][i + 3].name);
        }
        if(propArray[0][i + 4].id != 0)
        {
            SetPosition(MARGIN_X + 1 + 3*i,  INFO_START_Y + 4);
            printf("%d.%s",propArray[0][i + 4].id,propArray[0][i + 4].name);
        }
    }
    SetPosition(MARGIN_X + 1,  INFO_START_Y + 5);
    printf("输入商品编号查看商品简介或购买(按非以上序号返回)：\t");
    scanf("%d",&k);
    if(k <= 0 || k > 23)
        ShowMap();
    else
    {
        for(i = 0;i < 25;i++)
            if(k == propArray[0][i].id)
            {
                Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
                SetPosition(MARGIN_X + 31, INFO_START_Y + -1);
                printf("%d.%s:",propArray[0][i].id,propArray[0][i].name);
                SetPosition(MARGIN_X + 10, INFO_START_Y);
                if(propArray[0][i].type == Weapon)
                printf("属性(攻击)%d~%d",propArray[0][i].minAttack,propArray[0][i].maxAttack);
                if(propArray[0][i].type == Armor)
                printf("属性(防御)：%d~%d",propArray[0][i].minDefence,propArray[0][i].maxDefence);
                if(propArray[0][i].type == Con)
                printf("属性(效果)：%d~%d",propArray[0][i].minPower,propArray[0][i].maxPower);
                int descLen = strlen(propArray[0][i].desc);
                SetPosition(MARGIN_X + 10, INFO_START_Y + 2);
                for(j = 0; j < descLen; j++)
                {
                    if(j != 0 && j % 60 == 0)
                    {
                        SetPosition(MARGIN_X + 10, INFO_START_Y + j/60 + 2);
                    }
                    printf("%c", propArray[0][i].desc[j]);
                }
                SetPosition(MARGIN_X + 10, INFO_START_Y + 6);
                printf("此物品售价%d金币，是否购买？  (按Y购买/任意键返回)",propArray[0][i].price);
                n = getch();
                switch(n)
                {
                case 'Y':
                    if(currPlayer->gold > propArray[0][i].price)
                    {
                        currPlayer->gold -= propArray[0][i].price;
                        propArray[currPlayer->id][currPlayer->propCount] = propArray[0][i];
                    }
                    currPlayer->propCount++;
                    SetPosition(MARGIN_X + 65, INFO_START_Y + 6);
                    printf("购买成功");
                    break;
                default:
                    ShowMap();
                }
            }
    }
}


void SwitchE()
{
    int i,j,bh;
    int k = 0;
    int m = 0;
    int n = 1;
    int t = 0;
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 10, INFO_START_Y + -1);
    printf("1.切换武器\t\t 2.切换防具\t\t 3.返回");
    SetPosition(MARGIN_X + 35, INFO_START_Y);
    i = getch();
    SetPosition(MARGIN_X + 1, INFO_START_Y + 1);
    switch(i)
    {
    case '1':
        printf("您当前可用武器有：");
        for(j = 0;j < currPlayer->propCount;j++)
            if(propArray[currPlayer->id][j].type == Weapon)
                {
                    k++;
                    SetPosition(MARGIN_X + 20 + m, INFO_START_Y + k + n);
                    printf("%-2d.%s",propArray[currPlayer->id][j].id,propArray[currPlayer->id][j].name);
                    if(k%3 == 0 && k != 0)
                        m += 20, n = 1-k;
                }
            SetPosition(MARGIN_X + 1, INFO_START_Y + 6);
            printf("请输入你要切换的武器编号(按非以上序号返回)：  ");
            scanf("%d",&bh);
            for(j = 0;j < currPlayer->propCount;j++)
                if(propArray[currPlayer->id][j].id == bh && propArray[currPlayer->id][j].type == Weapon)
                {
                    t++;
                    currPlayer->weapon = propArray[currPlayer->id][j];
                    SetPosition(MARGIN_X + 55, INFO_START_Y + 6);
                    printf("切换成功，按方向键返回");
                }
            if(t==0)
                ShowMap();
        break;
    case '2':
        printf("您当前可用防具有：");
        for(j = 0;j < currPlayer->propCount;j++)
            if(propArray[currPlayer->id][j].type == Armor)
                {
                    k++;
                    SetPosition(MARGIN_X + 20 + m, INFO_START_Y + k + n);
                    printf("%-2d.%s",propArray[currPlayer->id][j].id,propArray[currPlayer->id][j].name);
                    if(k%3 == 0 && k != 0)
                        m += 20, n = 1-k;
                }
                SetPosition(MARGIN_X + 1, INFO_START_Y + 6);
            printf("请输入你要切换的防具编号(按非以上序号返回)：  ");
            scanf("%d",&bh);
            for(j = 0;j < currPlayer->propCount;j++)
                if(propArray[currPlayer->id][j].id == bh && propArray[currPlayer->id][j].type == Armor)
                {
                    t++;
                    currPlayer->armor = propArray[currPlayer->id][j];
                    SetPosition(MARGIN_X + 55, INFO_START_Y + 6);
                    printf("切换成功，按方向键返回");
                }
            if(t==0)
                ShowMap();
        break;
    case '3':
        ShowMap();
    }
}

void DeleteH()
{
    int i;
    int j;
    if(player_count <=1)
    {
        Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
        SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
        printf("当前只有一个角色，不能删除,按方向键返回");
    }
    else{
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 10, INFO_START_Y + -1);
    printf("请输入您想要删除的角色的编号(按、输入非以上序号返回)：");
    SetPosition(MARGIN_X + 20, INFO_START_Y);
    for(i = 0;i < player_count;i++)
        printf("%d.%s\t",i+1,players[i].name);
    SetPosition(MARGIN_X + 20, INFO_START_Y + 1);
    scanf("%d",&j);
    if(j <= 0 || j > player_count)
        ShowMap();
    else
    {
        if(currPlayer == &players[j - 1])
            currPlayer = &players[j - 2];
        players[j - 1] = players[j];
        SetPosition(MARGIN_X + 20, INFO_START_Y + 4);
        printf("角色删除成功，按方向键返回");
        player_count--;
    }
    }
}

void SwitchH()
{
    int i,k = 0,juese;
    char TempPassword[20];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    O:SetPosition(MARGIN_X + 15, INFO_START_Y);
    printf("请输入您想要使用的角色的编号(输入非以上序号返回)：");
    SetPosition(MARGIN_X + 20, INFO_START_Y + 2);
    for(i = 0;i < player_count;i++)
        printf("%d.%s\t",i+1,players[i].name);
    SetPosition(MARGIN_X + 20, INFO_START_Y + 3);
    scanf("%d",&juese);
    if(juese == 0 || juese > player_count)
        ShowMap();
    else
    {
    SetPosition(MARGIN_X + 20, INFO_START_Y + 4);
    printf("请输入您的密码：");
    Star(TempPassword);
    if(!strcmp(TempPassword,players[juese - 1].password))
    {
        currPlayer = &players[juese - 1];
        SetPosition(MARGIN_X + 20, INFO_START_Y + 5);
        printf("切换成功！");
        k++;
    }
    if(!k)
    {
        Clear(MARGIN_X + 20, INFO_START_Y + -1,8);
        SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
        printf("密码错误，请重新输入编号及密码");
        goto O;
    }
    }
}

void Rename()
{
    char s[50];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
    printf("亲爱的玩家，您当前的名称是：%s\n",currPlayer->name);
    SetPosition(MARGIN_X + 20, INFO_START_Y);
    printf("请输入新名称(输入\"0\"返回)：");
    scanf("%s",s);
    if(!strcmp(s,"0"))
        ShowMap();
    else
    {
        strcpy(currPlayer->name,s);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 1);
        printf("亲爱的玩家，您的名称已变为：%s\n",currPlayer->name);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 2);
        printf("按方向键返回");
    }
}

void Repassword()
{
    char nowpassword[20];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    Y:SetPosition(MARGIN_X + 20, INFO_START_Y);
    printf("请输入您当前密码：(输入\"0\"返回)：");
    SetPosition(MARGIN_X + 20, INFO_START_Y + 1);
    Star(nowpassword);
    if(!strcmp("0",nowpassword))
    {
        ShowMap();
    }
    else if(!strcmp(nowpassword,currPlayer->password))
    {
        SetPosition(MARGIN_X + 20, INFO_START_Y + 2);
        printf("请输入新密码：");
        Star(currPlayer->password);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 3);
        printf("修改成功，按方向键返回地图");
    }
    else
    {
        Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
        SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
        printf("密码错误，请重新输入！");
        goto Y;
    }

}

void Save()
{

    //打开存档文件
    if((fp = fopen("memory.txt","w+")) == NULL)
        {
            fprintf(stderr,"Can't open memory.txt!\n");
            exit(1);
        }

    //保存人物
    fwrite(&players,sizeof(players),1,fp);
    fwrite(&player_count,sizeof(player_count),1,fp);
    fwrite(&propArray,sizeof(propArray),1,fp);
    fclose(fp);
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 33, INFO_START_Y + 2);
    printf("存档成功！！");
}

void Login()
{
    int i,k=0;
    char TempID[20],TempPassword[20];
    Clear(MARGIN_X + 10,6,13);
    N:StartSquare();
    SetPosition(50,8);
    printf("请输入您的名讳：");
    SetPosition(50,9);
    scanf("%s",TempID);
    SetPosition(50,10);
    printf("请输入您的密码：");
    SetPosition(50,11);
    Star(TempPassword);
    for(i = 0;i < player_count;i++)
        if(!strcmp(TempID,players[i].name) && !strcmp(TempPassword,players[i].password))
        {
            currPlayer = &players[i];
            SetPosition(50,12);
            printf("登陆成功！");
            k++;
        }
    if(!k)
        {
            Clear(50,8,4);
            SetPosition(44,7);
            printf("用户名或密码错误，请重新输入！");
            goto N;
        }
}

void Register()
{
    int i,j;
    char s[50],password1[20],password2[20];
    Clear(MARGIN_X + 10,6,13);
    StartSquare();
    SetPosition(36, 8);
    printf("亲爱的玩家，请输入您的名讳(输入\"0\"返回):\t");
    SetPosition(36, 9);
    scanf("%s",s);
    if(!strcmp(s,"0"))
        Start();
    else
    {
        M:SetPosition(36, 11);
        printf("请输入您的密码：");
        Star(password1);
        SetPosition(36, 12);
        printf("请再次确认您的密码：");
        Star(password2);
        if(strcmp(password1,password2))
        {
            Clear(36, 10,4);
            SetPosition(36, 10);
            printf("两次输入不一致，请重新输入");
            goto M;
        }
        else
        {
            strcpy(players[player_count].name,s);
            for(i = 0;i < 12;i = i + 4)
            {
                SetPosition(36 + 3*i,  INFO_START_Y + 1);
                printf("%d.%s",martials[i].id,martials[i].name);
                if(martials[i + 1].id != 0)
                {
                    SetPosition(36 + 3*i,  INFO_START_Y + 2);
                    printf("%d.%s",martials[i + 1].id,martials[i + 1].name);
                }
                if(martials[i + 2].id != 0)
                {
                    SetPosition(36 + 3*i,  INFO_START_Y + 3);
                    printf("%d.%s",martials[i + 2].id,martials[i + 2].name);
                }
                if(martials[i + 3].id != 0)
                {
                    SetPosition(36 + 3*i,  INFO_START_Y + 4);
                    printf("%d.%s",martials[i + 3].id,martials[i + 3].name);
                }
            }
        }
    SetPosition(MARGIN_X + 20, INFO_START_Y);
    printf("亲爱的玩家，请输入您要加入的势力:");
    scanf("%d",&j);
    for(i = 0;i < 13;i++)
    {
        if(j == martials[i].id)
        players[player_count].martial = martials[j - 1];
    }
    players[player_count].weapon = propArray[0][0];

    players[player_count].id = player_count + 1;
    players[player_count].level = 1;
    players[player_count].exp = 50;
    players[player_count].hp = 100;
    players[player_count].gold = 5;
    players[player_count].propCount = 2;
    players[player_count].propMax = 8;
    propArray[player_count][0] = propArray[0][0];
    propArray[player_count][1] = propArray[0][15];
    players[player_count].weapon = propArray[player_count][0];
    players[player_count].armor = propArray[player_count][1];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    currPlayer = &players[player_count];
    player_count++;
    }
}

void StartSquare()
{
    SetPosition(MARGIN_X + 10,6);
    printf("------------------------------------------------------");
    for(int i = 0;i < 12;i++)
        {
            SetPosition(MARGIN_X + 10,7 + i);
            printf("|");
            SetPosition(MARGIN_X + 63,7 + i);
            printf("|");
        }
    SetPosition(MARGIN_X + 10,18);
    printf("------------------------------------------------------");
}

void StartMenu()
{
    char key;
    StartSquare();
    SetPosition(50,8);
    printf("1.老玩家回归");
    SetPosition(50,10);
    printf("2.新玩家注册");
    Q:key = getch();
    if(key == '1' || key == '2')
    {
        switch(key)
        {
        case '1':
            Login();
            break;
        case '2':
            Register();
            break;
        }
    }
    else
        goto Q;
    Clear(MARGIN_X,9,6);
}

void Load()
{
    if((fp = fopen("memory.txt","r")) == NULL)
        {
            fprintf(stderr,"No Game Cache Here!\n");
            exit(2);
        }
    fread(&players,sizeof(players),1,fp);
    fread(&player_count,sizeof(player_count),1,fp);
    fread(&propArray,sizeof(propArray),1,fp);
    fclose(fp);
}

void Start()
{
    SetPosition(39,1);
    printf("欢迎来到大型RPG - 《Game of Thrones》");
    SetPosition(44,20);
    Sleep(500);
    printf("游戏作者：李扬,康鹏灏,石涔熠");
    SetPosition(44,21);
    printf("创作日期：2019.5.16");

    StartMenu();
    Clear(MARGIN_X + 10,6,13);

    SetPosition(50,9);

    Sleep(100);
    printf("[Valar Morghulis]");
    SetPosition(40,10);

    printf("------------------------------------");

    SetPosition(39,11);
    printf("|");
    SetPosition(40,11);
    printf(">");

    SetPosition(76,11);
    printf("|");
    SetPosition(40,12);
    printf("------------------------------------");

    SetPosition(40,11);
    int i;
    for(i = 0; i < 35; i++) {
        printf(">");
        Sleep(50);
    }

    SetPosition(50,13);
    Sleep(100);
    printf("[Valar Dohaeris]");

    Sleep(3000);

    SetPosition(40,100);
    Clear(1, 1, 50);
}
