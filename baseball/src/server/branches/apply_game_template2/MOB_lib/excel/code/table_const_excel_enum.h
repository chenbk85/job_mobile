// 10_excel_enum.xls
#ifndef table_const_excel_enum_header_h_define4456
#define DEF_i_MAX_FRIEND  50  // �ִ� ģ����
#define DEF_i_SINGLEPLAY_1ROUND_TIME_MIN  3  // �Ѷ��� �÷��̿� �ʿ��� �ּҽð�(�̱ۿ��� ���¡üũ��)
#define DEF_i_TOTAL_ROUND  9  // �÷��̾ 10�� ġ�� 10�� ����
#define DEF_i_ATTACK_CHANGE_ROUND  3  // ������ ����Ǵ� ROUND��. 3�̸� 3���帶�� ���������.
#define DEF_i_MAX_PLAYER_CREATE_NUM  3  // �ִ� ���������� ����(���� or Ÿ��)
#define DEF_i_MAX_FRIEND_RECORD_MONTH  1  // ģ������ ������� 1����ġ�� ������. 
#define DEF_i_DEFAULT_USER_TEAM_COUNT  2  // �⺻������ ������ �����Ҽ��ִ� ����
#define DEF_i_MAX_USER_TEAM_COUNT  5  // ���������� �缭 Ȯ�尡���� �ִ� ����
#define DEF_i_MAX_PITCHER_SKILL_COUNT  10  // ������ �����Ҽ��ִ� ��ȭ�� ��ų�� ����- Tbl_PitcherSkill
#define DEF_i_MAX_PITCHER_SKILL_EQUIP  5  // ������ ���ӿ� ������� �ִ� ��ȭ�� ��ų��-Tbl_PitcherSkill
#define DEF_i_TIME_1_PLAYER_READY  10  // ������ ����� �ٸ��� �ڵ����� ��Ű�� �ð�
#define DEF_i_TIME_ALL_PLAYER_NOT_READY  20  // ��� ����  ���� �ʾ��� ��� �ڵ����� ��Ű�� �ð�
#define DEF_i_TIME_ALL_PLAYER_READY  5  // ��� ����  �Ͽ��� ��� 5�� ī��Ʈ �� ���İ� ����
#define DEF_i_TIME_PLAYER_INTRODUCE  5  // ���� ���� �� �����Ұ� ȭ���� ��� �ð��� 5�� ī��Ʈ. �÷��̾� ��� SKIP��ư  TAP�ÿ� ���� ����. �Ѹ� SKIP��ư TAP�ÿ�  ��밡 ���ӽ����� �غ��ϰ� �ֽ��ϴ�. ��� ����ϰ� 5�� �״�� ī��Ʈ 
#define DEF_i_TIME_GAME_FIRST_ATTACK_DECIDE_COUNT  2  // ����� ��� ���� ���� �� ���İ� ������ �ҿ�Ǵ� �ð��� 2���̴�. 
#define DEF_i_WAIT_TIME_PITCHER_THROW  12  // ���� ���Խÿ� ������ ���� ������ �ʰ� ��ٸ��� ���� �� �ڵ������� ��ȯ�Ǳ� �������� �ð�(��)
#define DEF_i_WAIT_TIME_BATTER_HIT  5  // ������ ���� ���� �� Ÿ�ڰ� ���� ĥ������ ������ ��ٷ��ִ� �ð�(��). �̽ð��� ������ 
#define DEF_i_TIME_GAME_ROUND_CHANGE_TEAM  7  // ���İ������Ǿ� ���ӽ��� �� ���İ� ü���� �� ����ð�. ��ȹ������ �׷��ȿ������̶� ������ ����.
#define DEF_i_TIME_RESULT_WHEN_AUTOPLAY  20  // ������ ������ ����������� �������� Ŭ�� �ڵ��÷����� �Ѷ������� �޴µ� ��ٸ��½ð�(��)
#define DEF_i_TIME_GAME_ROUND  3  // ���尡 ���������� ������Ÿ��. ��ȹ������ �׷��ȿ������̶� ������ ����.
#define DEF_i_TIME_GAME_ROUND_TEAMCHANGE  3  // ��� ���峡���� ���� �ٲ� ��ٸ��½ð�
#define DEF_i_TIME_GAME_ROUND_END  3  // ��������� ���� ������ ����������Ŷ�� �������� �Ҷ� ��ٸ��½ð�
#define DEF_i_THROW_PER_ROUND  9  // �� ���Ӵ� ������ ��
#define DEF_i_ROUND_PER_GAME  1  // �� ������ �� �� ���� ��
#define DEF_i_MAX_PLAYING_USER  2  // ���� �÷��̽� �����ϴ� ������
#define DEF_i_PITCHER_THROW_POSITION_SIZE  9  // ������ ���� ������ ���� ��ġ ���� ( 3 BY 3 =9��)
#define DEF_b_IS_FIRST_ATTACK_USER_IS_RANDOM false // ������ �����ϰ� ���� ���������� ������ �����ڷ� ����.
#define DEF_i_ID_PACKAGE  5000  // Sys_Package id�� 5001���ͽ���
#define DEF_i_GAMECOUNT_EXP_SINGLEPLAY_IN_DAY  3  // �Ϸ� ���� �̱� �÷��̷� ����ġ�� �������ִ� Ƚ��
#endif //table_const_excel_enum_header_h_define4456




#define for_each_table_const_excel_enum(X) \
X(i_MAX_FRIEND ,  50  , "�ִ� ģ����")\
X(i_SINGLEPLAY_1ROUND_TIME_MIN ,  3  , "�Ѷ��� �÷��̿� �ʿ��� �ּҽð�(�̱ۿ��� ���¡üũ��)")\
X(i_TOTAL_ROUND ,  9  , "�÷��̾ 10�� ġ�� 10�� ����")\
X(i_ATTACK_CHANGE_ROUND ,  3  , "������ ����Ǵ� ROUND��. 3�̸� 3���帶�� ���������.")\
X(i_MAX_PLAYER_CREATE_NUM ,  3  , "�ִ� ���������� ����(���� or Ÿ��)")\
X(i_MAX_FRIEND_RECORD_MONTH ,  1  , "ģ������ ������� 1����ġ�� ������. ")\
X(i_DEFAULT_USER_TEAM_COUNT ,  2  , "�⺻������ ������ �����Ҽ��ִ� ����")\
X(i_MAX_USER_TEAM_COUNT ,  5  , "���������� �缭 Ȯ�尡���� �ִ� ����")\
X(i_MAX_PITCHER_SKILL_COUNT ,  10  , "������ �����Ҽ��ִ� ��ȭ�� ��ų�� ����- Tbl_PitcherSkill")\
X(i_MAX_PITCHER_SKILL_EQUIP ,  5  , "������ ���ӿ� ������� �ִ� ��ȭ�� ��ų��-Tbl_PitcherSkill")\
X(i_TIME_1_PLAYER_READY ,  10  , "������ ����� �ٸ��� �ڵ����� ��Ű�� �ð�")\
X(i_TIME_ALL_PLAYER_NOT_READY ,  20  , "��� ����  ���� �ʾ��� ��� �ڵ����� ��Ű�� �ð�")\
X(i_TIME_ALL_PLAYER_READY ,  5  , "��� ����  �Ͽ��� ��� 5�� ī��Ʈ �� ���İ� ����")\
X(i_TIME_PLAYER_INTRODUCE ,  5  , "���� ���� �� �����Ұ� ȭ���� ��� �ð��� 5�� ī��Ʈ. �÷��̾� ��� SKIP��ư  TAP�ÿ� ���� ����. �Ѹ� SKIP��ư TAP�ÿ�  ��밡 ���ӽ����� �غ��ϰ� �ֽ��ϴ�. ��� ����ϰ� 5�� �״�� ī��Ʈ ")\
X(i_TIME_GAME_FIRST_ATTACK_DECIDE_COUNT ,  2  , "����� ��� ���� ���� �� ���İ� ������ �ҿ�Ǵ� �ð��� 2���̴�. ")\
X(i_WAIT_TIME_PITCHER_THROW ,  12  , "���� ���Խÿ� ������ ���� ������ �ʰ� ��ٸ��� ���� �� �ڵ������� ��ȯ�Ǳ� �������� �ð�(��)")\
X(i_WAIT_TIME_BATTER_HIT ,  5  , "������ ���� ���� �� Ÿ�ڰ� ���� ĥ������ ������ ��ٷ��ִ� �ð�(��). �̽ð��� ������ ")\
X(i_TIME_GAME_ROUND_CHANGE_TEAM ,  7  , "���İ������Ǿ� ���ӽ��� �� ���İ� ü���� �� ����ð�. ��ȹ������ �׷��ȿ������̶� ������ ����.")\
X(i_TIME_RESULT_WHEN_AUTOPLAY ,  20  , "������ ������ ����������� �������� Ŭ�� �ڵ��÷����� �Ѷ������� �޴µ� ��ٸ��½ð�(��)")\
X(i_TIME_GAME_ROUND ,  3  , "���尡 ���������� ������Ÿ��. ��ȹ������ �׷��ȿ������̶� ������ ����.")\
X(i_TIME_GAME_ROUND_TEAMCHANGE ,  3  , "��� ���峡���� ���� �ٲ� ��ٸ��½ð�")\
X(i_TIME_GAME_ROUND_END ,  3  , "��������� ���� ������ ����������Ŷ�� �������� �Ҷ� ��ٸ��½ð�")\
X(i_THROW_PER_ROUND ,  9  , "�� ���Ӵ� ������ ��")\
X(i_ROUND_PER_GAME ,  1  , "�� ������ �� �� ���� ��")\
X(i_MAX_PLAYING_USER ,  2  , "���� �÷��̽� �����ϴ� ������")\
X(i_PITCHER_THROW_POSITION_SIZE ,  9  , "������ ���� ������ ���� ��ġ ���� ( 3 BY 3 =9��)")\
X(b_IS_FIRST_ATTACK_USER_IS_RANDOM , false , "������ �����ϰ� ���� ���������� ������ �����ڷ� ����.")\
X(i_ID_PACKAGE ,  5000  , "Sys_Package id�� 5001���ͽ���")\
X(i_GAMECOUNT_EXP_SINGLEPLAY_IN_DAY ,  3  , "�Ϸ� ���� �̱� �÷��̷� ����ġ�� �������ִ� Ƚ��")\
 
