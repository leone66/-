#include "Game.h"
#include "GameLib.h"

#define SEP "------------------------------------------------------------------------------"
#define COL 78      //��Ϸ�����ܿ��
#define MARGIN_X 20 //��߾�
#define MAP_START_Y 3   //��ͼ�Ŀ�ʼ����
#define MAP_END_Y 11
#define INFO_START_Y 13
#define MAIN_MENU_START_Y 22

FILE * fp;
int X = 0, Y = 0;
int player_count = 2;
//Ӣ��
Player players[100] = {
    {001, "�Ǹ�����", "123456789",  99, 0, 999999, 999999 ,5,8},
    {002, "Τ����˹",   "123456abc",  1,  0, 100,    5      ,2,8},
};


Martial martials[] ={
    {1,  "����"      , .hqCoord.X=7, .hqCoord.Y=3, 1, "ά˹�����½��ͳ����"},
    {2,  "̹������"  , .hqCoord.X=6, .hqCoord.Y=7, 1, "̹����������ķ��ԭ���Ǻ�ˮ���ڵĵ���Ǳ���ʯ�����������ߴ������������߹��׶����ٳǣ�ͳ��ά˹�����������֮�á�̹����������������Ǻڵ׺�ɫ�Ķ�����ͷ������������š������ߡ�����һ���Լ����Ľ�������άɣ���Ǻ�����˿��̹����������������ǡ�Ѫ��ͬԴ�������׳�Ϊ����������"},
    {3,  "ʷ����"    , .hqCoord.X=1, .hqCoord.Y=1, 1, "ʷ���˼����Ǳ�������ϡ����Ժ�Ҳ������Ҫ�ļ��壬���ǵ���ʷ����׷�ݵ��������ߡ������ǡ���һ��Ӣ�ۼ�Ԫʱ�ڵĴ�����������ٶ��ǵĽ����ߣ����;�����һ��Э�������˾��������Է����������֡��ڡ������ߡ�������֮�󳤴Ｘǧ���У�ʷ���˼��嶼�Ǳ���֮�����ڽ��������ס�ʷ����������������Ͷ���󣬱�����Ϊ̹����������ͳ��֮�µ��ߴ�����֮һ��ʷ���˼��屻��Ϊ�����ػ�����Ϯ��ְ��"},
    {4,  "����˹��"  , .hqCoord.X=4, .hqCoord.Y=5, 1, "����Ǳ�Ϊ���ҳǣ������糺���ϵĽ�ɫ�غ���ʨ������Ϊ������ŭ�𡱡����⣬����һ�����ʽ�ĸ��ԣ�������˹����ծ�ػ�������仰�����ȼ������Ը�����������˹�ؼ��屾��һ����Ϊ����Х�����������Ǹֽ��������ڶ�ʧ�ˡ�����˹�����Խ𷢰׷����ߴ���Ϊ������"},
    {5,  "����ϯ��"  , .hqCoord.X=6, .hqCoord.Y=2, 1, "�ߴ����������İ���ϯ�����嵮��������ս��ʱ�ڣ����Ĵ������Ǳ�ҥ��Ϊ������˽���ӵܵܵİ���˹������ϯ��������˹������ϯ������ս���Ժգ����ϱ���Σ��ɳ�Ϊ�������ĸɽ�֮һ��������˹������ս���ڼ���ܲ�ɱ�����һ�η籩�����Դ�ġ��Ƕ�����������˹������ϯ��Ȣ���Ƕ�������Ů�������̳��˷籩���ļһա������Ϊ�˵�һ�η�Ϣ������������ϯ������ļһ���һֻ���۵Ĵ������ڵĺ�¹��������ŭ����ԭ"},
    {6,  "ͽ��"      , .hqCoord.X=3, .hqCoord.Y=3, 1, "�����ǵ�ͽ�������ǺӼ�ص���Ҫ���壬Ҳ������ꪺ������ͳ���ߡ��ұ�Ϊ�����ǡ�����ʷ����׷�ݵ�Ӣ�ۼ�Ԫ�ı����������ǣ������Ǵ�δ���������ǵļһ�����Ծ�ں������Ƶ��ϵ���ɫ���㣬�����������ǡ����壬���Σ���������"},
    {7,  "������"    , .hqCoord.X=5, .hqCoord.Y=0, 1, "�������������Ӵ�����У���ԣ�̶Ƚ���������˹�ؼ��壬���ܶ�Ա����ǿ�ľ������������⣬��������������������·⳼�׵��¼���Ͷ����е��Ľ��ӣ����Ϻ�������Ч�Ҽ���ĺ�������ô������������ӵ�еĵĺ��Ͼ������������ڻʼҽ��ӡ����ߴ������У��������Ǹ���ʷ�ƾã���������ʿ����ļ��壬���ǳ���'�߽��ػ�'��'���������ͳ��'�Է⡣���������һ��ʢ���������Ұ֮�ϵĽ�õ�壻����Ϊ��������Ϣ��"},
    {8,  "����"      , .hqCoord.X=3, .hqCoord.Y=2, 1, "ӥ���ǵİ��ּ����ǹȵ�����Ҫ�ļ��塣���ּ���ķ��Ϊӥ���ǣ���������Ҳ����������Ǳ������ǵı�־������ɫ��ɫ�ϣ�һֻ�ڰ�ɫ����֮�ϰ��������ɫ��ӥ�����ǵ������ǡ�������ҫ����"},
    {9, "��̩��"    , .hqCoord.X=6, .hqCoord.Y=1, 1, "����÷��˹����Ϊ����÷���ǵ�Ѫ��������ꪳ������ǵ�ͳ�����ġ�ͨ���������Ϊ��̩�����塣��̩������ļһ���һ���ᴩ���յĽ�ǹ����ǹ�ǹŴ���̩���ļһգ��������������ã����������ǡ��������ӡ�����̩�����˵���ò�ǵ��͵����ˣ��������Ե������������������������ɫ��Ƥ�������ۺڷ����������������Ա��������ɫ��ͷ����"},
    {10, "��������"  , .hqCoord.X=3, .hqCoord.Y=4, 1, "��Ⱥ��λ��ά˹�����½���棬�����Ͽᣬ���ξ��͡�����������Ժ�������Ϊ�����Դ�Ϊ�٣������������һֻ��ɫ�׳ĵĽ�ɫ���֣�����Ϊ��ǿȡʤ�ڿ����"},
    {11, "��ҹ��"    , .hqCoord.X=0, .hqCoord.Y=0, 1, "��ҹ����һ��ר�������������ǵľ��š�����������λ���ߴ����������߾�����������������ľ޴�ĳ�ǽ�����Ž�����Ӣ�ۼ�Ԫʱ��������ֱ�����֮����ҹ��ֻ���ź��¡�"},
    {12, "���"      , .hqCoord.X=0, .hqCoord.Y=6, 1, "��˵�У�8000���ڳ���ʱ�䳤��һ���������ݶ����Ǹ���������ҹ�������ڰ�ʱ�������һ�ν����˼䡣���գ����Ǳ������ɭ��֮�����ϻ��ˣ����������Ǳ������������������һ���Զ��׼���ì����ʵ�ǣ���˵��ҹ��Ȣ��һλ�����һ����Ů�ˣ������������ܺ����ʹ������伣���ڳ��������𽥱�Ϊ�������Ż�С���ӵĴ�����񻰹��¡�����ά˹�������ڻ�������ʱ�Ի��������Ϊ��ͷ�"}
};

Monster monsterArray[] = {
    {1,  "С͵",       1, 60,  3,   8,   8,   10,  10,   1, {4, 4}},
    {2,  "ǿ��",       2, 100, 5,   12,  10,  18,  30,   1, {4, 4}},
    {3,  "ǿ�鷸",     3, 150, 6,   15,  15,  20,  50,   1, {4, 4}},
    {4,  "����",       3, 230, 7,   20,  25,  35,  100,  1, {0, 0}},
    {5,  "���±�",     3, 300, 9,   28,  40,  50,  200,  1, {0, 0}},
    {6,  "Ұ��",       4, 350, 10,  30,  55,  70,  500,  1, {4, 0}},
    {7,  "Ұ����ԭ��", 4, 400, 12,  40,  60,  75,  800,  1, {1, 1}},
    {8,  "��ҹ����ͽ", 3, 300, 18,  45,  65,  85,  1000, 1, {4, 0}},
    {9,  "ʬ��",       5, 500, 30,  80,  70,  90,  1200, 1, {1,0}},
    {10, "�������",   5, 500, 40,  100, 75,  100, 1500, 1, {2,0}},
    {11, "������ʿ",   8, 800, 60,  120, 80,  120, 1800, 1, {5,2}},
    {12, "����",       7, 700, 70,  180, 80,  130, 2000, 1, {1,7}},
    {13, "����",       7, 700, 85,  180, 80,  130, 2500, 1, {2,7}},
    {14, "ҹ��",       9, 900, 100, 230, 100, 150, 4000, 1, {6,0}},
    {15, "����",       9, 900, 150, 200, 150, 200, 6000, 1, {6,0}},
};

Map mapArray[8][8] ={
    {
        {1, "�ڳǱ�",   1, {0, 0}, "��ҹ�˵���Ҫ���ݣ�λ���������Զ�����ľ�������������������ģ��ڹ�����������ľ�ͷ��"},
        {2, "����ȭ��", 1, {1, 0}, "������Ԫʱ�������������Ļ���������λ������ӱߡ���������ҹ�˵�����ȭ��֮ս�����ĵط���"},
        {3, "˪ѩ֮��", 1, {2, 0}, "˪ѩ֮��������Ӱ����������ȭ��Ķ����������Ǳ���ҹ�˳�Ϊ���ҵ������߷�֮һ��"},
        {4, "����Ͽ",   1, {3, 0}, "λ������ͨ��˪ѩ֮����һ��ͨ������������Ϊ��紩��Ͽ�ڣ���������޺����������"},
        {5, "��˹�ر�", 1, {4, 0}, "������һ�����������ϵı��ݣ���ν����ֻ��������ҹ�˸�ȡ�����֡������ڳ����Ա������������ǿ�˹�أ�һ����Ƣ����Ұ�ˣ�ͬʱҲ����ҹ�˵����ѡ�"},
        {6, "��������", 1, {5, 0}, "�Ǿ�����������25�������ء���Ƭ�����ɡ������ߡ�������������ĳ����Ϊ�����ǡ�ʷ���˵ı���֮�����͸���ҹ�ˡ�"},
        {7, "��������", 1, {6, 0}, "�������ߴ����������ش����ɱ�ѩ���ɵľ޴�ķ������£��佫������Ұ�˵����طָ�������������˵�˪ѩ֮��ɽ����һֱ��������˵ĺ����塣"},
        {8, "������",   1, {7, 0}, "����һ�����塣��λ�ڳ����Զ���һֱ���쵽������İ��ؼ�����ء���ҹ�˵ĳǱ��������������ں����尶�ߡ�˹����˹����λ�����С�"}
    },
    {
        {9,  "����¯", 1, {0, 1}, "���ؼ���ļұ�����λ�ÿ��������ؽ���ĩ�������ڳ����Ķ���������������ߡ���������Ķ��ߡ�������ҹ�˵ı��ݣ����ı�¯�Ǿ����ߴ�������ĳǱ��ˡ�"},
        {10, "�ٶ���",   1, {1, 1}, "ʷ���˼����洫�ĳǱ���Ȩ�������ģ�����Ϊ�Ǳ������׸������������ߴ���������ʡ�ݵ����ģ����������������ٺͳ�������������"},
        {11, "������",   1, {2, 1}, "������ʷ���˼���ļұ�����һ����̵ı��ݣ�λ�ڱ����Ķ�������������ϱߣ��������Ǵ��ͱڡ�"},
        {12, "�ֲ���",   1, {3, 1}, "���ټ���ĳǱ�����λ�ڴ�½���࣬�������Ὥ����"},
        {13, "��ˮ��",   1, {4, 1}, "���λ�ھ����ڲ�������������Ϸ�����ˮ��û��ѧʿ��Ҳû����ʿ������ʦ������ʷ������������ˡ����񡢷��׼��������������ͼ������ˮ���ľ��ӣ����Ҷ��Ҳ�������"},
        {14, "���ֱ�",   1, {5, 1}, "��������ľӵء�λ�ں����Ǳ����������������ɽ���ϵ�һ��ľͷ���ݡ���ϯ��������������˵�����������ǻ�ɽ�ϵ�ľ�������"},
        {15, "������",   1, {6, 1}, "�Ǳ�����һ��Ҫ����λ�ڶ�֫���뺣�ڣ��Ѹ��������ߡ�"},
        {16, "���׷���", 1, {7, 1}, "�չ�����ľӳǣ�λ���ٶ��ǵ����Ϸ��Ĵ���ߡ����ĳ�ǽ����ʯ������ʮ�߸ߣ��ĽǸ���һ�����������뻹��һ�����εﱤ�����Ǹ���̵ı��ݡ�"}


    },
    {
        {17, "�ϳ�",     1, {0, 2}, "��˼���ľӳǣ�λ�ڱ���ҧ�����ذ��� "},
        {18, "�Ѹ���",   1, {1, 2}, "�Ѹ����ķ����ؼ������ء��������λ�ü�����ά˹�����½����ߡ�Ҳ�ܿ��������ĺ�����"},
        {19, "�׸�",     1, {2, 2}, "һ����ۿڳ��У��������ٶ����Ϸ����������ռ���ķ�ء��׸��Ǿ����Ա����ľ�ס�أ�����ά˹��������������С�ġ��׸��Ǳ�����Ҫ��ó�׸ۿڣ���λ�ڰ��кӺӿڣ������ṩ�����ó�׻���ȥ�����ĵ�����"},
        {20, "����³�", 1, {3, 2}, "λ�ڱ����Ŀֲ�����׸�֮�䣬�ǻ���¼���ļұ���"},
        {21, "������",   1, {4, 2}, "�޴��ӵؾ��󱱶˵�һ�������Ǳ������Ǳ�����һ���֣�����ʷ���˼���Ĺ�Ͻ�������Ѿ��м����������˾�ס����������������þ��Ӱ�ȫͨ������ĵ̵���������Ϊ��ǧ������������������Ϸ����Ե�ս��Ҫ�ء�"},
        {22, "��ڣ��",   1, {5, 2}, "��ʱҲ��������ڣ���Ǳ�������Ҫ���򣬴�˹������ļұ���ڣ��Ҳ�����ڴˡ��������������ڣ�ϣ��ӽ���������������ì̲�ĺ�������"},
        {23, "��ʯ��",   1, {6, 2}, "�Ǻ���صĸ���������ļұ�"},
        {24, "ĺ����",   1, {7, 2}, "�佨�ڸۿ��ԣ���·�ɶ���ʯ�̾ͣ������˼������ء��Ǳ���һ����ɫ���£���·�ں�����ʯ����Сɽ�����졣��������岼�����������·�ߡ����������ʯ�뵺����ͣ���Ĵ�ֻ���������ϵķ籩Ϯ����"}


    },
    {
        {25, "��˹�ȳ�", 1, {0, 3}, "����˹�ȼ���ļұ���λ�ھ��ٱ������Ǿ��ٵ�ĺ����Ľݾ�����˹�ȴ��򲻴󣬵�����ľ��������ɵ�С�ݡ�"},
        {26, "�Ϻӳ�",   1, {1, 3}, "�ֳƺӶɿڣ��Ƿ��׼����ڶɺӿڴ���Ҫ����λ�ںӼ�ء�Ҫ�ӱ��������Ӽ�أ��˴����̲�����¼�������Ψһ�Ķɺӵ㣬���������ڴ��ٶ��ǵ������ǵĴ�·�ϡ�"},
        {27, "ӥ����",   1, {2, 3}, "�����������ϵĴ���֮һ���Թ������ļұ���������������ɽ���Ķ��ˣ�������֮ǹ���ȵؾ������ڼ�ǧӢ�ߵ��·���ӥ���Ǳ���Ϊ���޷����Ƶġ�"},
        {28, "������",   1, {3, 3}, "ͽ�������洫��ǧ��ļұ����ڰ�����������ڼ�����������ͽ�����˽�����������λ����ʯ��������ཻ֮����"},
        {29, "�ɿ˵�",   1, {4, 3}, "�ɿ˵������ɿ˳Ǻ;����ۡ��������ǲ���������ľӵأ����ɿ˳�����ĸۿڡ��ɿ˵�������嵺��һ��ĺ��̡�"},
        {30, "���ױ�",   1, {5, 3}, "����һ����������ս��֮ǰ�ľ޴�Ǳ���λ�ںӼ�أ������ۺ����������ߴ����������ı��ݡ����Դ�����ս����������һֱ����һ����������Ŀ����ĵط���"},
        {31, "������",   1, {6, 3}, "������һ��Ҫ����������¼���ļұ����������ŴӺӼ�ش���ɽ��ֱ��������һ�������ͨ������£���Ҫ�����������ͱ����������½����ǡ�"},
        {32, "���ٳ�",   1, {7, 3}, "�ߴ��������׶���λ��ά˹���嶫���������ˮ�塣�Ǻ챤�����������������������ڵء����б���ǽ�����ƣ���ǽ�������ر�����פ�أ����߳�֮Ϊ�������ӡ�������Ҳ���ߴ�������һ����Ҫ�ۿڣ���λ�����ھ���"},
    },
    {
        {33, "��ˮ��",   1, {0, 4}, "��ά˹���嶫���һƬ�޴�ĺ��塣λ�������к�ˮ�ӻ�������֮����ֻ�к�������������������߹����Ǿ��پ�λ�ں�ˮ��ӿڡ���������һ�����صĵر���Ϊ������֮ì������ˮ������ˮ�ƴ�"},
        {34, "����",     1, {1, 4}, "�Ǿ��ٳ��ϲ���ب��ˮ���һƬɭ�֡�"},
        {35, "��ʯ��",   1, {2, 4}, "һ��λ�ں�ˮ����ڴ��ĵ��죬��Ǳ�����̳�������״����ʯ��ԭΪ�������������ɱ�������������̹����������ķ�ء�"},
        {36, "�챤",     1, {3, 4}, "�ߴ�����֮�����Ļʹ����������߹��׶����ٵ���������֮�ϡ�"},
        {37, "������",   1, {4, 4}, "���ٵ�ƶ��ߡ����ǳ��е�һƬ�ͼ�����С�������ܸ㵽'����'��С�ꡣ��Ȧ����Ǻ�Ƥ����ɢ�����ĳ�ζ�����ھƽѺͼ�Ժ����ζ�"},
        {38, "���ҳ�",   1, {5, 4}, "�����׸�������˹�ؼ����ͳ�����ڡ� ���ҳǺ������ϵ���˼һ��������һ��޴����ʯ�ϵ�̶��ɣ��޽�������ĳ�ǽ������������ʹ�óǱ��ķ�����������ǿ����ʵ�ϣ����ҳǴ�δ�������"},
        {39, "����˹��", 1, {6, 4}, "�ڶ���ۿڳ��У�����������֮���ذ����ڿ��ҳ��������Ӽ������ƽ����ͱ����������ĵط���"},
        {40, "��˹��÷", 1, {7, 4}, "λ�����ҳǺ���������������ӵ�зḻ�Ľ�����������⳼��Ү˹����ķ�ء���Ү˹������Ϊð��������˹�ؼ��壬����̩����˹�ز�����"}

    },
    {
        {41, "��ͥ",     1, {0, 5}, "�Ǻ����λ�����º��ϵĳǱ������߹�ʱ��������԰������ľӳǣ�����ս���Ժ󱻴͸������������塣"},
        {42, "����",     1, {1, 5}, "ά˹�����ģ���ĸۿڣ���������֮һ��Ҳ����������ϵ�һ���������ڰ����������ǰ���������񽨳ɡ�"},
        {43, "��ͤ��",   1, {4, 5}, "��ά˹���������ϱߵ�һ�����죬���׵��¼���ͳ�Ρ�"},
        {44, "�����",   1, {3, 5}, "�ǰ¿˺��ؼ�����層��λ�ں���ء���λ���ں����������������������д���[2]����������Ƕ���ͨ����ͥ��"},
        {45, "������",   1, {5, 5}, "�����������層����λ�ں���ء���λ�ں���Զ�����ͥ������"},
        {46, "���º�",   1, {6, 5}, "�Ǻ�������ĺ�������ˮ�����޴󣬺�����������ž�λ�ڸú�֮�ϡ�"},
        {47, "���̲",   1, {7, 5}, "λ�ں���أ�����������ӡ�������᯷�¼������أ��������Ҫ���������֣����̲�������̲������̲�ݳ���"},
        {48, "ʢ����",   1, {7, 5}, "����̹������������Ĺ��������Ǳ�ֻ������������¡�"}
    },

    {
        {49, "��׹��",   1, {0, 6}, "��λ�ڶ��������֮�����ߡ�������һ������Ϊ��ʯ�����ĸ�������׹�������Ŷ�����������塣"},
        {50, "��ꪳ�",   1, {1, 6}, "��̩������ĳǱ���������׸�����λ����Ѫ���Ա���������ά˹�����½�Ķ��Ϻ��������滷�������������˽��ס����ˮ��԰λ����ꪳ����������ĺ�̲�ߣ�һ��������·�����Ƿֿ���"},
        {51, "��Ϣ��",   1, {2, 6}, "�ߴ����������̵ĳǱ�֮һ���ǰ���ϯ������ļ�����������֮ǰ�ļ�ǧ�꣬�ǹ��ϵķ籩������λ���Ǳ���˵����֯�ڳ�ǽ�ڵ��������������Է�ֹħ��ͨ����ǽ��"},
        {52, "��ͥ",     1, {3, 6}, "�����λ�����º��ϵĳǱ������߹�ʱ��������԰������ľӳǣ�����ս���Ժ󱻴͸������������塣"},
        {53, "��˹��",   1, {4, 6}, "ά˹�����ذ��ĸ�������֮һ��������˹����ķ�أ����ǵľӳ�λ�ڵ��ϵ�ĺ��������˹�������Ƕ����������������ڱ���Ϊ�Ƿ籩�ص�һ���֡���˹�������Ϣ��Ч�ҡ�"},
        {54, "ʢ��Ⱥ��", 1, {5, 6}, "λ��ά˹����Ͷ�˹��˹���ϣ���˹��˹�����ĺ����Ⱥ����������������֮��������������֮������֪�������ͼ�б�ע��ʢ��Ⱥ���������������Լ�����С����δ֪�Ϸ��Ƿ��и���ĵ��졣"},
        {55, "ʯ���е�", 1, {6, 6}, "λ�������е�һϵ��Ⱥ�����Ӷ������ֱ������֮�ء�ʯ���е��Ǻ����ǵĳ�Ѩ���е��н��������������֣�Ѫʯ���ͻҽʼܵ�������ó�׳ǰ�֮һ��̩����Ҳλ��ʯ���е��С�"},
        {56, "ǧ����",   1, {7, 6}, "ǧ���������ۺ��е�һ��С������ά˹�����ϲ�Ψһ����������ľ�ĵط���"}
    },
    {
        {57, "����˹",   1, {0, 7}, "����˹����֪���������ĸۿ�֮һ��ά˹����������ȱ���ĸ���ɫ���ƺ�ȫ�ܵ��˿���˹������˹Ϊ�Լ��Ĺ��ᱣ���ŵ����ľ޴���ͷ��"},
        {58, "��˹����", 1, {1, 7}, "ū�����һ�����У����������Ӻӿڡ����Գ���һ�������ū�������޹��߶��������ڵ�����˿����֮ǰ������һֱ������ͳ���š�"},
        {59, "Ԩ��",     1, {2, 7}, "ū���嶫������һ�����С�����Ҫ������ū���������������ū��������е�ҡҡ��׹�ĳ�ǽ�͸������н��ݽ�������ȫ�ɻ�ɫ��ש�齨�ɣ���һȺ�����������˵�ū����ͳ���š�"},
        {60, "����",     1, {3, 7}, "ū�����һ���ǰ�����ں������ߣ�������˹���������ϡ�����ū��ó�׶�������"},
        {61, "��˹����", 1, {4, 7}, "��˹��˹��½�ϵ�һ�����ԭ��λ������ó�׳ǰ�Ķ��������������������˹�����ˡ�"},
        {62, "������˹", 1, {5, 7}, "λ������ó�׳ǰ�Ķ��Ͻǣ�����֮�ض���������ӵ��뺣�ڣ��Ǿ��������������������ó�׳ǰ"},
        {63, "��������", 1, {6, 7}, "һ�������Ѿõĳ��У�Ҳ��һ�����˾�̾�ĳ��У���������Ϊ�����������ɱ��ݵ۹��Ķ��ǡ������������Ϊ��������ĩ�պƽٵ��������¼������µġ�̹����������ķ�Դ�ء�"},
        {64, "����",     1, {7, 7}, "λ����֪�������Ϸ������ش���˹��˹��½���Ϸ���һ��Ш�εؿ�ļ�ˣ�������غ컨��Ͽ���紦һ���ۿڳ��С����ĵĶ��������Ǵ�˵�б���Ӱ���֡�����Ϊ��Ӱ֮�ص�����"}
    },
};

//����
Prop propArray[10][25] = {
    {
        {1,    "ذ��",        1,  1,  30,    Weapon, .minAttack = 0,    .maxAttack = 5,    "�̿ͱر�" },
        {2,    "����",        1,  1,  50,    Weapon, .minAttack = 3,    .maxAttack = 4,    "ά˹�����½ʿ���õ���ͨ����"},
        {3,    "�������䵶",  1,  1,  50,    Weapon, .minAttack = 1,    .maxAttack = 5,    "��˹�����˹㷺ʹ�õ�����"},
        {4,    "������˹��",  1,  1,  60,    Weapon, .minAttack = 2,    .maxAttack = 4,    "��˹�����˹㷺ʹ�õ�����"},
        {5,    "ս��",        2,  1,  60,    Weapon, .minAttack = 3,    .maxAttack = 6,    "���յ����׸������ָ��������������׺Ͷ���"},
        {6,    "����",        2,  1,  70,    Weapon, .minAttack = 3,    .maxAttack = 6,    "���ٵĶ���������װ��" },
        {7,    "����",        3,  1,  80,    Weapon, .minAttack = 4,    .maxAttack = 7,    "���Խ������250��Զ������͸���˰��"},
        {8,    "ʮ�ֹ�",      5,  1,  100,   Weapon, .minAttack = 6,    .maxAttack = 8,    "�Ǵ���������"},
        {9,    "�ܶ�ʮ�ֹ�",  7,  1,  200,   Weapon, .minAttack = 8,    .maxAttack = 12,   "��һ�������֧���"},
        {10,   "Ұ�˳�ì",    1,  1,  50,    Weapon, .minAttack = 2,    .maxAttack = 5,    "����Ұ���õ�ì�������򵥵���ɱ������"},
        {11,   "��ǹ",        2,  1,  80,    Weapon, .minAttack = 3,    .maxAttack = 6,    "�ӳ��ĳ�ì�������������еı�־������"},
        {12,   "���Ǵ�",      3,  1,  200,   Weapon, .minAttack = 8,    .maxAttack = 12,   "���Ϻ����Ӵ��Ľ��ף���ǿ׳���޷���Ԧ"},
        {13,   "��������ذ",  8,  1,  3000,  Weapon, .minAttack = 15,   .maxAttack = 18,   "����ϡ�����������Ǹ��Ƴɣ������̶Ⱥ�Ӳ�ȶ���������"},
        {14,   "���ǹ�",      8,  1,  500,   Weapon, .minAttack = 12,   .maxAttack = 15,   "���ǹ��������Զ����һ��ľ����һ�����󣬲��õ���˹�����˵ĸ߶�����"},
        {15,   "�������ǽ�",  10, 1,  5000,  Weapon, .minAttack = 18,   .maxAttack = 20,   "����ϡ���������������Ǹֽ���ӵ��һ�������Լ��Ĵ�˵���ͼ��ߵ�����"},
        {16,   "�ӵ��",      1,  1,  80,    Armor,  .minDefence = 50,  .maxDefence = 80,  "��Ƥ��򷫲�������ͨ���ò��ϼ������,����Ϊ����ס�"},
        {17,   "�ۼ�",        2,  1,  150,   Armor,  .minDefence = 80,  .maxDefence = 100, "���ֻ��׵�����ͨ���ɷ�������Ƥ��������Ƴɣ�����������Ƕ��һ���г����ν���Ƭ"},
        {18,   "������",      3,  1,  300,   Armor,  .minDefence = 100, .maxDefence = 120, "���ֻ���һ��һ�����Ӷ��ɣ����뻷����������ͬһ�ֶ���"},
        {19,   "��װ���",    4,  1,  500,   Armor,  .minDefence = 120, .maxDefence = 150, "��װ������"},
        {20,   "������",      6,  1,  800,   Armor,  .minDefence = 200, .maxDefence = 250, "��������������,�������"},
        {21,   "����",        5,  1,  500,   Con,    .minPower = 0,     .maxPower = 999,   "�����Ǻ���ʯ��ɭ��֮������������ذ�ס����С���ͷ���������������������Ϊ������Ŀ���֮һ"},
        {22,   "ҹӰ֮ˮ",    9,  1,  1000,  Con,    .minPower = 999,   .maxPower = 800,   "�������ÿ������Ƿ��գ����ù���������ó�˯"},
        {23,   "��˹֮��",    10, 1,  1000,  Con,    .minPower = 999,   .maxPower = 1000,  "��һ�ַǳ��������۸�߰��Ķ�ҩ������ζ��������ˮ�������ھ��л���ˮ�У��᲻��Ҳ������"}
    },
    {
        {99,   "�Ѹ�֮��",    10, 50, 8000,  Weapon, .minAttack = 20,   .maxAttack = 25,   "�Ǵ��������,�����ɶƽ�ӣ��ľ�Ƴɣ����Ϲ��͵ĺ�Ƥ�������װ���Ŵ���ʨ��ͷ"},
        {98,   "����",        9,  50, 8000,  Weapon, .minAttack = 16,   .maxAttack = 18,   "�Ǵ��������,�����ϵ�Բ����һö�и�����εĺ챦ʯ��Ƕ��ʨ���У����������������Ѫ��"},
        {8,    "ʮ�ֹ�",      5,  1,  30,    Weapon, .minAttack = 6,    .maxAttack = 8,    "�Ǵ���������"},
        {999,  "����֮��",    10, 50, 8000,  Armor,  .minDefence = 400, .maxDefence = 600, "ȡ����֮�����ϳɵĶ�"},
        {1000, "�Թ�",        8,  50, 10000, Con,    .minPower = 999,   .maxPower = 1000,  "�Ǵ�����ã�����ʹ�ñ��ⷴ��"}
    },
    {
        {2,    "����",        1,  1,  50,    Weapon,  .minAttack = 3,   .maxAttack = 4,    "ά˹�����½ʿ���õ���ͨ����"},
        {17,   "�ۼ�",        2,  1,  150,   Armor,  .minDefence = 80,  .maxDefence = 100, "���ֻ��׵�����ͨ���ɷ�������Ƥ��������Ƴɣ�����������Ƕ��һ���г����ν���Ƭ"},
    }
};

Player *currPlayer;

//��ʼ��
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
                printf("��С��������%d\t��󹥻�����%d\n", currPlayer->weapon.minAttack, currPlayer->weapon.maxAttack);
                break;
            case Armor:
                printf("��С��������%d\t����������%d\n", currPlayer->weapon.minDefence, currPlayer->weapon.maxAttack);
                break;
            case Con:
                printf("��С����ֵ��%d\t�������ֵ��%d\n", currPlayer->weapon.minPower, currPlayer->weapon.maxPower);
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
                //����ڵ�ǰλ�ã��͸��ĵ�ͼ��ɫ
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
    //�����Ϣ������Ϣ
    //SetPosition(MARGIN_X + 5, INFO_START_Y + 1);

    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
    printf("��ǰ������ڵ�ͼ��%s", mapArray[Y][X].name);
    SetPosition(MARGIN_X + 10, INFO_START_Y);

    //��������
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
    printf("������Ϸ�Ҹ�");
    SetPosition(MARGIN_X + 1,  INFO_START_Y );
    printf("���Ʋ�����Ϸ���ܾ�������Ϸ��");
    SetPosition(MARGIN_X + 49,  INFO_START_Y );
    printf("ע�����ұ�����������ƭ�ϵ���");
    SetPosition(MARGIN_X + 1,  INFO_START_Y + 2 );
    printf("�ʶ���Ϸ���ԣ�������Ϸ����");
    SetPosition(MARGIN_X + 49,  INFO_START_Y + 2);
    printf("������ʱ�䣬���ܽ������");
    SetPosition(MARGIN_X + 27,  INFO_START_Y + 4 );
    printf("����Ϸ�ܾ�16�������߷��ʣ�");
    SetPosition(MARGIN_X + 33,  INFO_START_Y + 5 );
    printf("�����������...");
}
void showMainMenu()
{
    Clear(MARGIN_X + 1, MAIN_MENU_START_Y - 1, 7);
    SetPosition(MARGIN_X + 35, MAIN_MENU_START_Y - 1);
    printf("��Ϸ�˵�");
    SetPosition(MARGIN_X + 1,  MAIN_MENU_START_Y );
    printf("1.��������");
    SetPosition(MARGIN_X + 16, MAIN_MENU_START_Y );
    printf("2.���ҹ���");
    SetPosition(MARGIN_X + 31, MAIN_MENU_START_Y );
    printf("3.�ؼ�");
    SetPosition(MARGIN_X + 46, MAIN_MENU_START_Y );
    printf("4.����װ��");
    SetPosition(MARGIN_X + 61, MAIN_MENU_START_Y );
    printf("5.�л�װ��");
    SetPosition(MARGIN_X + 1,  MAIN_MENU_START_Y + 2);
    printf("6.�л���ɫ");
    SetPosition(MARGIN_X + 16, MAIN_MENU_START_Y + 2);
    printf("7.�޸�����");
    SetPosition(MARGIN_X + 31, MAIN_MENU_START_Y + 2);
    printf("8.ɾ����ɫ");
    SetPosition(MARGIN_X + 46, MAIN_MENU_START_Y + 2);
    printf("9.��������");
    SetPosition(MARGIN_X + 61, MAIN_MENU_START_Y + 2);
    printf("X.��Ϸ�浵");
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
    printf("Ӣ��<%s>�ĸ�����������", currPlayer->name);
    SetPosition(MARGIN_X + 5, INFO_START_Y);
    printf("�ȼ���%d\tѪ����%d\t������%d~%d\t������%d~%d", currPlayer->level, currPlayer->hp, currPlayer->level*2 + currPlayer->weapon.minAttack,
    currPlayer->level*2 + currPlayer->weapon.maxAttack,currPlayer->level + currPlayer->armor.minDefence,currPlayer->level + currPlayer->armor.maxDefence);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 1);
    printf("����ֵ��%d\t��ң�%d\t\t\t����������%s",currPlayer->exp,currPlayer->gold,currPlayer->martial.name);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 3);
    printf("��ǰ������%s(������%d~%d)\t��ǰ���ߣ�%s(������%d~%d)", currPlayer->weapon.name, currPlayer->weapon.minAttack,
    currPlayer->weapon.maxAttack, currPlayer->armor.name, currPlayer->armor.minDefence, currPlayer->armor.maxDefence);
    SetPosition(MARGIN_X + 5, INFO_START_Y + 6);
    printf("�����������");
}

void ShowMonsters()
{
    char *levelNames[] = {"����é®", "��ͨƤë", "����ſ�", "����С��", "�������", "��и�ɻ�", "�������", "��������", "���˺�һ"};
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    //SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
    //printf("��ǰ��ͼ<%s>�Ĺ�������", mapArray[Y][X].name);
    //��������
    int monsterCount = sizeof(monsterArray) / sizeof(Monster);
    //��ǰ��ͼ�Ĺ����±�����
    int MonsterIndexs[9];
    //��ǰ��ͼ�Ĺ�������
    int currMapMonsterCount = 0;
    int i;
    for(i = 0; i < monsterCount; i++)
    {
        //���ҵ�ǰ��ͼ�Ĺ�������
        if(monsterArray[i].coord.X == X && monsterArray[i].coord.Y == Y && monsterArray[i].state != 0)
        {
            MonsterIndexs[currMapMonsterCount] = i;
            currMapMonsterCount++;
            if(currMapMonsterCount == 9)
                break;
        }
    }
        //��ӡ����
        SetPosition(MARGIN_X + 10, INFO_START_Y);
        if(currMapMonsterCount == 0)
        {
            printf("��ǰ��ͼ���������");
            return;
        }
        SetPosition(MARGIN_X + 25, INFO_START_Y - 1);
        printf("��ǰ��ͼ<%s>�Ĺ�������", mapArray[Y][X].name);
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

    /***************����PK*****************/
    //ѡ��Ҫ��Ĺ�����
    int PKMonsterId;
    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    printf("������Ҫ�����Ĺ���(��\"0\"����)��");
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
                    printf("�������");
                }
        }

}

void Fight(int monsterId)
{
    int monsterIndex = -1;  //���ҵĹ����±�
    int i = 0;
    for(i = 0; i < sizeof(monsterArray) / sizeof(Monster); i++)
    {
        if(monsterArray[i].id == monsterId)
        {
            monsterIndex = i;
            break;
        }
    }
    //û���ҵ�
    if(monsterIndex == -1)
    {
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        printf("Ҫ��ս�Ĺ��ﲻ���ڣ��밴���������");
        return;
    }
    //����������
    /*
    if(monsterIndex != -1) {
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);
        SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
        printf("�Ѿ�������ս���ս��������ʼ");
        return;
    }
    */
    int fightCount = 0;
    while(1)
    {
            //��ʼ���
            srand(time(NULL));
            //��ҵĹ�����
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
                printf("ս����%d��, %sHP:%d\t%sHP:%d", fightCount, currPlayer->name, currPlayer->hp, monsterArray[monsterIndex].name, monsterArray[monsterIndex].hp);
                usleep(1000 * 100);

    }

    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    Clear(MARGIN_X + 5, INFO_START_Y + 4, 1);

    if(currPlayer->hp <= 0)
        {
            SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
            printf("��ѻ������Ӣ��<%s>���ڹ���<%s>��ս����׳������", currPlayer->name, monsterArray[monsterIndex].name);
            currPlayer->hp = 100;
            return;
    }
    SetPosition(MARGIN_X + 5, INFO_START_Y + 4);
    printf("��ѻ������<%s>��ɱ�������%d�����%d���(�����������)", monsterArray[monsterIndex].name, monsterArray[monsterIndex].exp, monsterArray[monsterIndex].maxMoney);
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
    printf("��ӭ���ٲ�����˹");
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
    printf("������Ʒ��Ų鿴��Ʒ������(����������ŷ���)��\t");
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
                printf("����(����)%d~%d",propArray[0][i].minAttack,propArray[0][i].maxAttack);
                if(propArray[0][i].type == Armor)
                printf("����(����)��%d~%d",propArray[0][i].minDefence,propArray[0][i].maxDefence);
                if(propArray[0][i].type == Con)
                printf("����(Ч��)��%d~%d",propArray[0][i].minPower,propArray[0][i].maxPower);
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
                printf("����Ʒ�ۼ�%d��ң��Ƿ���  (��Y����/���������)",propArray[0][i].price);
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
                    printf("����ɹ�");
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
    printf("1.�л�����\t\t 2.�л�����\t\t 3.����");
    SetPosition(MARGIN_X + 35, INFO_START_Y);
    i = getch();
    SetPosition(MARGIN_X + 1, INFO_START_Y + 1);
    switch(i)
    {
    case '1':
        printf("����ǰ���������У�");
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
            printf("��������Ҫ�л����������(����������ŷ���)��  ");
            scanf("%d",&bh);
            for(j = 0;j < currPlayer->propCount;j++)
                if(propArray[currPlayer->id][j].id == bh && propArray[currPlayer->id][j].type == Weapon)
                {
                    t++;
                    currPlayer->weapon = propArray[currPlayer->id][j];
                    SetPosition(MARGIN_X + 55, INFO_START_Y + 6);
                    printf("�л��ɹ��������������");
                }
            if(t==0)
                ShowMap();
        break;
    case '2':
        printf("����ǰ���÷����У�");
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
            printf("��������Ҫ�л��ķ��߱��(����������ŷ���)��  ");
            scanf("%d",&bh);
            for(j = 0;j < currPlayer->propCount;j++)
                if(propArray[currPlayer->id][j].id == bh && propArray[currPlayer->id][j].type == Armor)
                {
                    t++;
                    currPlayer->armor = propArray[currPlayer->id][j];
                    SetPosition(MARGIN_X + 55, INFO_START_Y + 6);
                    printf("�л��ɹ��������������");
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
        printf("��ǰֻ��һ����ɫ������ɾ��,�����������");
    }
    else{
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 10, INFO_START_Y + -1);
    printf("����������Ҫɾ���Ľ�ɫ�ı��(���������������ŷ���)��");
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
        printf("��ɫɾ���ɹ��������������");
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
    printf("����������Ҫʹ�õĽ�ɫ�ı��(�����������ŷ���)��");
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
    printf("�������������룺");
    Star(TempPassword);
    if(!strcmp(TempPassword,players[juese - 1].password))
    {
        currPlayer = &players[juese - 1];
        SetPosition(MARGIN_X + 20, INFO_START_Y + 5);
        printf("�л��ɹ���");
        k++;
    }
    if(!k)
    {
        Clear(MARGIN_X + 20, INFO_START_Y + -1,8);
        SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
        printf("������������������ż�����");
        goto O;
    }
    }
}

void Rename()
{
    char s[50];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
    printf("�װ�����ң�����ǰ�������ǣ�%s\n",currPlayer->name);
    SetPosition(MARGIN_X + 20, INFO_START_Y);
    printf("������������(����\"0\"����)��");
    scanf("%s",s);
    if(!strcmp(s,"0"))
        ShowMap();
    else
    {
        strcpy(currPlayer->name,s);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 1);
        printf("�װ�����ң����������ѱ�Ϊ��%s\n",currPlayer->name);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 2);
        printf("�����������");
    }
}

void Repassword()
{
    char nowpassword[20];
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    Y:SetPosition(MARGIN_X + 20, INFO_START_Y);
    printf("����������ǰ���룺(����\"0\"����)��");
    SetPosition(MARGIN_X + 20, INFO_START_Y + 1);
    Star(nowpassword);
    if(!strcmp("0",nowpassword))
    {
        ShowMap();
    }
    else if(!strcmp(nowpassword,currPlayer->password))
    {
        SetPosition(MARGIN_X + 20, INFO_START_Y + 2);
        printf("�����������룺");
        Star(currPlayer->password);
        SetPosition(MARGIN_X + 20, INFO_START_Y + 3);
        printf("�޸ĳɹ�������������ص�ͼ");
    }
    else
    {
        Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
        SetPosition(MARGIN_X + 20, INFO_START_Y + -1);
        printf("����������������룡");
        goto Y;
    }

}

void Save()
{

    //�򿪴浵�ļ�
    if((fp = fopen("memory.txt","w+")) == NULL)
        {
            fprintf(stderr,"Can't open memory.txt!\n");
            exit(1);
        }

    //��������
    fwrite(&players,sizeof(players),1,fp);
    fwrite(&player_count,sizeof(player_count),1,fp);
    fwrite(&propArray,sizeof(propArray),1,fp);
    fclose(fp);
    Clear(MARGIN_X + 1, INFO_START_Y - 1, 8);
    SetPosition(MARGIN_X + 33, INFO_START_Y + 2);
    printf("�浵�ɹ�����");
}

void Login()
{
    int i,k=0;
    char TempID[20],TempPassword[20];
    Clear(MARGIN_X + 10,6,13);
    N:StartSquare();
    SetPosition(50,8);
    printf("�������������䣺");
    SetPosition(50,9);
    scanf("%s",TempID);
    SetPosition(50,10);
    printf("�������������룺");
    SetPosition(50,11);
    Star(TempPassword);
    for(i = 0;i < player_count;i++)
        if(!strcmp(TempID,players[i].name) && !strcmp(TempPassword,players[i].password))
        {
            currPlayer = &players[i];
            SetPosition(50,12);
            printf("��½�ɹ���");
            k++;
        }
    if(!k)
        {
            Clear(50,8,4);
            SetPosition(44,7);
            printf("�û���������������������룡");
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
    printf("�װ�����ң���������������(����\"0\"����):\t");
    SetPosition(36, 9);
    scanf("%s",s);
    if(!strcmp(s,"0"))
        Start();
    else
    {
        M:SetPosition(36, 11);
        printf("�������������룺");
        Star(password1);
        SetPosition(36, 12);
        printf("���ٴ�ȷ���������룺");
        Star(password2);
        if(strcmp(password1,password2))
        {
            Clear(36, 10,4);
            SetPosition(36, 10);
            printf("�������벻һ�£�����������");
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
    printf("�װ�����ң���������Ҫ���������:");
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
    printf("1.����һع�");
    SetPosition(50,10);
    printf("2.�����ע��");
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
    printf("��ӭ��������RPG - ��Game of Thrones��");
    SetPosition(44,20);
    Sleep(500);
    printf("��Ϸ���ߣ�����,�����,ʯ���");
    SetPosition(44,21);
    printf("�������ڣ�2019.5.16");

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
