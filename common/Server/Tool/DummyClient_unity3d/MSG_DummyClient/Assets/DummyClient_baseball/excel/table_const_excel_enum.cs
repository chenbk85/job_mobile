// 10_excel_enum.xls
namespace nEXCEL{ public class table_const_excel_enum{
public const bool b_IS_FIRST_ATTACK_USER_IS_RANDOM = false; // ������ �����ϰ� ���� ���������� ������ �����ڷ� ����.
public const bool b_IS_GIVE_DAILY_BONUS_TO_ALL = false; // �̰��� true�̸� �����Ҷ����� ������ ��������Ʈ ���ʽ��� ����
public const int i_ATTACK_CHANGE_ROUND =  3 ; // ������ ����Ǵ� ROUND��. 3�̸� 3���帶�� ���������.
public const int i_DEFAULT_USER_TEAM_COUNT =  2 ; // �⺻������ ������ �����Ҽ��ִ� ����
public const int i_GAMECOUNT_EXP_SINGLEPLAY_IN_DAY =  3 ; // �Ϸ� ���� �̱� �÷��̷� ����ġ�� �������ִ� Ƚ��
public const int i_DEFAULT_GAME_MONEY =  10000 ; // ���ʰ��ӽ��۽� ���������ִ� ���ӸӴ�
public const int i_MAX_FRIEND =  50 ; // �ִ� ģ����
public const int i_MAX_FRIEND_RECORD_MONTH =  1 ; // ģ������ ������� 1����ġ�� ������. 
public const int i_MAX_PITCHER_SKILL_COUNT =  10 ; // ������ �����Ҽ��ִ� ��ȭ�� ��ų�� ����- Tbl_PitcherSkill
public const int i_MAX_PITCHER_SKILL_EQUIP =  5 ; // ������ ���ӿ� ������� �ִ� ��ȭ�� ��ų��-Tbl_PitcherSkill
public const int i_MAX_PLAYER_CREATE_NUM =  3 ; // �ִ� ���������� ����(���� or Ÿ��)
public const int i_MAX_PLAYING_USER =  2 ; // ���� �÷��̽� �����ϴ� ������
public const int i_MAX_USER_TEAM_COUNT =  5 ; // ���������� �缭 Ȯ�尡���� �ִ� ����
public const int i_MAX_PLAYER_SKILL_STICKER =  10 ; // ����Ư���ɷ� ��ƼĿ�� �ִ� 10��
public const int i_MAX_BREAKING_BALL_STICKER =  10 ; // ��ȭ�� ��ƼĿ�� �ִ� 10��
public const int i_PITCHER_THROW_POSITION_SIZE =  9 ; // ������ ���� ������ ���� ��ġ ���� ( 3 BY 3 =9��)
public const int i_ROUND_PER_GAME =  1 ; // �� ������ �� �� ���� ��
public const int i_SINGLEPLAY_1ROUND_TIME_MIN =  3 ; // �Ѷ��� �÷��̿� �ʿ��� �ּҽð�(�̱ۿ��� ���¡üũ��)
public const int i_THROW_PER_ROUND =  9 ; // �� ���Ӵ� ������ ��
public const int i_TIME_CLIENT_REPEAT_SEND_PACKET =  1500 ; // ����-msec Ŭ���̾�Ʈ�� �Ȱ��� ��Ŷ�� �������� ������ �ִ� �ּҽð�
public const int i_TIME_1_PLAYER_READY =  1 ; // ������ ����� �ٸ��� �ڵ����� ��Ű�� �ð�
public const int i_TIME_ALL_PLAYER_NOT_READY =  1 ; // ��� ����  ���� �ʾ��� ��� �ڵ����� ��Ű�� �ð�
public const int i_TIME_ALL_PLAYER_READY =  1 ; // ��� ����  �Ͽ��� ��� 5�� ī��Ʈ �� ���İ� ����
public const int i_TIME_GAME_FIRST_ATTACK_DECIDE_COUNT =  1 ; // ����� ��� ���� ���� �� ���İ� ������ �ҿ�Ǵ� �ð��� 2���̴�. 
public const int i_TIME_GAME_ROUND =  1 ; // ���尡 ���������� ������Ÿ��. ��ȹ������ �׷��ȿ������̶� ������ ����.
public const int i_TIME_GAME_ROUND_CHANGE_TEAM =  1 ; // ���İ������Ǿ� ���ӽ��� �� ���İ� ü���� �� ����ð�. ��ȹ������ �׷��ȿ������̶� ������ ����.
public const int i_TIME_GAME_ROUND_END =  1 ; // ��������� ���� ������ ����������Ŷ�� �������� �Ҷ� ��ٸ��½ð�
public const int i_TIME_GAME_ROUND_TEAMCHANGE =  1 ; // ��� ���峡���� ���� �ٲ� ��ٸ��½ð�
public const int i_TIME_PLAYER_INTRODUCE =  1 ; // ���� ���� �� �����Ұ� ȭ���� ��� �ð��� 5�� ī��Ʈ. �÷��̾� ��� SKIP��ư  TAP�ÿ� ���� ����. �Ѹ� SKIP��ư TAP�ÿ�  ��밡 ���ӽ����� �غ��ϰ� �ֽ��ϴ�. ��� ����ϰ� 5�� �״�� ī��Ʈ 
public const int i_TIME_RESULT_WHEN_AUTOPLAY =  20 ; // ������ ������ ����������� �������� Ŭ�� �ڵ��÷����� �Ѷ������� �޴µ� ��ٸ��½ð�(��)
public const int i_TOTAL_ROUND =  9 ; // �÷��̾ 10�� ġ�� 10�� ����
public const int i_WAIT_TIME_AFTER_GAME_END =  60 ; // ���� ���� �� ������ �ƹ��� �ൿ�� ���� �� ��� �ð�( ���� ����ġ ��û �� �ʱ�ȭ �� )
public const int i_WAIT_TIME_BATTER_HIT =  1 ; // ������ ���� ���� �� Ÿ�ڰ� ���� ĥ������ ������ ��ٷ��ִ� �ð�(��). �̽ð��� ������ 
public const int i_WAIT_TIME_PITCHER_THROW =  1 ; // ���� ���Խÿ� ������ ���� ������ �ʰ� ��ٸ��� ���� �� �ڵ������� ��ȯ�Ǳ� �������� �ð�(��)
}}
