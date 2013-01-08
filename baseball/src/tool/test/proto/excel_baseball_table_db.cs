using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;


namespace nPROTO
{
    [ProtoContract] 
    public class s_tbl__playerbase
    {
	    [ProtoMember(1, IsRequired = false)]
        public long db_id {get; set;} 	// Tbl__PlayerBase_id_t [PK index] 선수 database table PK 
	    [ProtoMember(2, IsRequired = false)]
	    public int sid {get; set;} 	// Sys_PlayerCard_id_t [Sys_Player아이디] 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 
	    [ProtoMember(3, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [유저번호]  
	    [ProtoMember(4, IsRequired = false)]
		public string pname {get; set;} 	// aname32_t [닉네임]  
	    [ProtoMember(5, IsRequired = false)]
		public int city {get; set;} 	// EPlayerNationType [출신국가] 캐주얼야구 게임기획서 3차 (20111031).docx참조 
	    [ProtoMember(6, IsRequired = false)]
		public string initial_name {get; set;} 	// aname32_t [이니셜] 생성시 세팅. 등뒤의이니셜글자. 중복가능 
	    [ProtoMember(7, IsRequired = false)]
		public int back_number {get; set;} 	// int16 [백넘버] 생성시 세팅. 변경아이템으로 변경가능 
	    [ProtoMember(8, IsRequired = false)]
		public int age {get; set;} 	// int16 [나이] 생성시 세팅. 
	    [ProtoMember(9, IsRequired = false)]
		public int body_type {get; set;} 	// EPlayerBodyType [체형]  
	    [ProtoMember(10, IsRequired = false)]
		public bool is_left {get; set;} 	// bool [좌우타입] 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 
	    [ProtoMember(11, IsRequired = false)]
		public long exp {get; set;} 	// long [경험치] 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 
	    [ProtoMember(12, IsRequired = false)]
		public int questcomplete_count {get; set;} 	// Sys_Quest_id_t [퀘스트완료_카운트] 완료 퀘스트 카운트 
	    [ProtoMember(13, IsRequired = false)]
		public int win_continue {get; set;} 	// int16 [연승] 연속으로 승리한 개수 
	    [ProtoMember(14, IsRequired = false)]
		public int lose_continue {get; set;} 	// int16 [연패] 연속 패한 개수 
	    [ProtoMember(15, IsRequired = false)]
		public long last_game_result {get; set;} 	// Tbl_Result_id_t [마지막경기id] 마지막으로 플레이한 경기결과 식별자 
	    [ProtoMember(16, IsRequired = false)]
		public int win_tot {get; set;} 	// int [총전적_승] 토탈 승 카운트 
	    [ProtoMember(17, IsRequired = false)]
		public int lose_tot {get; set;} 	// int [총전적_패] 토탈 패 카운트 
	    [ProtoMember(18, IsRequired = false)]
		public int win_season {get; set;} 	// int [시즌전적_승] 시즌 승 카운트(3개월) 
	    [ProtoMember(19, IsRequired = false)]
		public int lose_season {get; set;} 	// int [시즌전적_패] 시즌 패 카운트(3개월) 
	    [ProtoMember(20, IsRequired = false)]
		public string skill_sticker {get; set;} 	// aname1024_t [특수능력이름] Sys_PlayeSkillSticker에서의 name  ";"로 구분되어 여러개입력 
	    [ProtoMember(21, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [is_deleted]  
	    [ProtoMember(22, IsRequired = false)]
		public string date_insert {get; set;} 	// SYSTEMTIME [등록시간] 최초게임등록일 
	    [ProtoMember(23, IsRequired = false)]
		public string date_update {get; set;} 	// SYSTEMTIME [수정된시간] 마지막수정시간 
	    [ProtoMember(24, IsRequired = false)]
		public int elo_point {get; set;} 	// int [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
	    [ProtoMember(25, IsRequired = false)]
		public long team {get; set;} 	// Tbl_Team_id_t [소속팀id] 소속된 팀번호 
    }//massage s_tbl__playerbase



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
    public class s_tbl_friend
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_Friend_id_t [id]  
	    [ProtoMember(2, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [유저번호]  
	    [ProtoMember(3, IsRequired = false)]
		public long uid_fiend {get; set;} 	// Tbl_User_id_t [친구번호]  
	    [ProtoMember(4, IsRequired = false)]
		public string nic_fiend {get; set;} 	// aname32_t [친구이름]  
	    [ProtoMember(5, IsRequired = false)]
		public bool is_blocked {get; set;} 	// bool [is_blocked] 블랙리스트이냐? 
	    [ProtoMember(6, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [is_deleted]  
	    [ProtoMember(7, IsRequired = false)]
		public int win {get; set;} 	// int [친구전적승]  
	    [ProtoMember(8, IsRequired = false)]
		public int lose {get; set;} 	// int [친구전적패]  
    }//massage s_tbl_friend



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
    public class s_tbl_item
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_Item_id_t [고유식별자] db pk 
	    [ProtoMember(2, IsRequired = false)]
		public int sid {get; set;} 	// Sys__ItemBase_id_t [구매한 아이템종류] Sys__ItemBase_id_t 
	    [ProtoMember(3, IsRequired = false)]
		public int category {get; set;} 	// EItemCategory [대분류] 장비 스텁 소비 구분 
	    [ProtoMember(4, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [소유자id]  
	    [ProtoMember(5, IsRequired = false)]
		public long used_player_id {get; set;} 	// Tbl__PlayerBase_id_t [귀속된선수ID] 귀속된 선수id이며 소모용아이템은 특별히귀속되지않고쓴다.캐쉬인벤 or 게임인벤 환불여부가 결정된다 
	    [ProtoMember(6, IsRequired = false)]
		public string upgrade_level {get; set;} 	// aname32_t [업그레이드등급] baseball.xml에서 ITEM_UPGRADE_LOGIC 참조 
	    [ProtoMember(7, IsRequired = false)]
		public string date_end_upgrade {get; set;} 	// SYSTEMTIME [업그레이드진행완료시간] 현제시간보다 미래의 시간이 세팅되면 업그레이드상태이다. 
	    [ProtoMember(8, IsRequired = false)]
		public string etc_info {get; set;} 	// aname32_t [기타정보] 등번호 아이템일때는 등번호. 마킹 아이템일때는 마킹글자를 저장. 
	    [ProtoMember(9, IsRequired = false)]
		public bool is_equiped {get; set;} 	// bool [장착상태] 장착아이템의경우 장착상태인지 여부 
	    [ProtoMember(10, IsRequired = false)]
		public string date_expire {get; set;} 	// SYSTEMTIME [기간제아이템의사용시간] 기간제아이템의경우 사용가능한 시간 
	    [ProtoMember(11, IsRequired = false)]
		public string date_insert {get; set;} 	// SYSTEMTIME [구매한날짜] 구매한날짜 
	    [ProtoMember(12, IsRequired = false)]
		public string date_update {get; set;} 	// SYSTEMTIME [수정된시간] 마지막수정시간 
	    [ProtoMember(13, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
	    [ProtoMember(14, IsRequired = false)]
		public int state {get; set;} 	// EItemState [아이템상태]  
	    [ProtoMember(15, IsRequired = false)]
		public int use_count {get; set;} 	// int16 [사용가능한 경기횟수] 소비(컨슘)의경우 사용가능한 게임의 경기 횟수. 재료(스텁)의경우 보유갯수(중첩갯수) 
    }//massage s_tbl_item



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_item_admin
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_Item_id_t [고유식별자] db pk 
	    [ProtoMember(2, IsRequired = false)]
		public long rid {get; set;} 	// Tbl_Result_id_t [게임결과식별자] 보상아이템의경우 해당경기결과 식별자 
	    [ProtoMember(3, IsRequired = false)]
		public int bought_real_money {get; set;} 	// real_money_t [구매캐쉬] 구매시 사용한 리얼캐쉬 
	    [ProtoMember(4, IsRequired = false)]
		public int bought_point_money {get; set;} 	// real_money_t [구매포인트] 구매시 사용한 포인트 
	    [ProtoMember(5, IsRequired = false)]
		public int bought_game_money {get; set;} 	// game_money_t [구매게임머니] 구매시 사용한 게임머니 
	    [ProtoMember(6, IsRequired = false)]
		public int item_buy_type {get; set;} 	// EItemBuyType [구매상태] 아이템획득경로 정보 ( 보상아이템  또는 상점구매  or 이벤트) 
	    [ProtoMember(7, IsRequired = false)]
		public int shop_id {get; set;} 	// Sys_Shop_id_t [상점판매번호] 상점으로부터 구매한경우 상점판매정보 
    }//massage s_tbl_item_admin



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_pitcherskill
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_PitcherSkill_id_t [고유번호]  
	    [ProtoMember(2, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [소유자id]  
	    [ProtoMember(3, IsRequired = false)]
		public long pid {get; set;} 	// Tbl_PlayerPitcher_id_t [소유투수id] 디펄트명은 pp_name이다 
	    [ProtoMember(4, IsRequired = false)]
		public int gesture {get; set;} 	// EGestureType [제스쳐타입] 제스쳐종류 
	    [ProtoMember(5, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [삭제플레그]  
	    [ProtoMember(6, IsRequired = false)]
		public int exp {get; set;} 	// int [투수변화구 진행 시간] 각각의 변화구에 진행된 시간을 기록 
	    [ProtoMember(7, IsRequired = false)]
		public int type {get; set;} 	// EPlayerBreakingBall [투수변화구종류] 투수 변화구종류 
    }//massage s_tbl_pitcherskill



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_playerbetter
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl__PlayerBase_id_t [PK index] 선수 database table PK 
	    [ProtoMember(2, IsRequired = false)]
		public int sid {get; set;} 	// Sys_PlayerCard_id_t [Sys_Player아이디] 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 
	    [ProtoMember(3, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [유저번호]  
	    [ProtoMember(4, IsRequired = false)]
		public string pname {get; set;} 	// aname32_t [닉네임]  
	    [ProtoMember(5, IsRequired = false)]
		public int city {get; set;} 	// EPlayerNationType [출신국가] 캐주얼야구 게임기획서 3차 (20111031).docx참조 
	    [ProtoMember(6, IsRequired = false)]
		public string initial_name {get; set;} 	// aname32_t [이니셜] 생성시 세팅. 등뒤의이니셜글자. 중복가능 
	    [ProtoMember(7, IsRequired = false)]
		public int back_number {get; set;} 	// int16 [백넘버] 생성시 세팅. 변경아이템으로 변경가능 
	    [ProtoMember(8, IsRequired = false)]
		public int age {get; set;} 	// int16 [나이] 생성시 세팅. 
	    [ProtoMember(9, IsRequired = false)]
		public int body_type {get; set;} 	// EPlayerBodyType [체형]  
	    [ProtoMember(10, IsRequired = false)]
		public bool is_left {get; set;} 	// bool [좌우타입] 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 
	    [ProtoMember(11, IsRequired = false)]
		public long exp {get; set;} 	// long [경험치] 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 
	    [ProtoMember(12, IsRequired = false)]
		public int questcomplete_count {get; set;} 	// Sys_Quest_id_t [퀘스트완료_카운트] 완료 퀘스트 카운트 
	    [ProtoMember(13, IsRequired = false)]
		public int win_continue {get; set;} 	// int16 [연승] 연속으로 승리한 개수 
	    [ProtoMember(14, IsRequired = false)]
		public int lose_continue {get; set;} 	// int16 [연패] 연속 패한 개수 
	    [ProtoMember(15, IsRequired = false)]
		public long last_game_result {get; set;} 	// Tbl_Result_id_t [마지막경기id] 마지막으로 플레이한 경기결과 식별자 
	    [ProtoMember(16, IsRequired = false)]
		public int win_tot {get; set;} 	// int [총전적_승] 토탈 승 카운트 
	    [ProtoMember(17, IsRequired = false)]
		public int lose_tot {get; set;} 	// int [총전적_패] 토탈 패 카운트 
	    [ProtoMember(18, IsRequired = false)]
		public int win_season {get; set;} 	// int [시즌전적_승] 시즌 승 카운트(3개월) 
	    [ProtoMember(19, IsRequired = false)]
		public int lose_season {get; set;} 	// int [시즌전적_패] 시즌 패 카운트(3개월) 
	    [ProtoMember(20, IsRequired = false)]
		public string skill_sticker {get; set;} 	// aname1024_t [특수능력이름] Sys_PlayeSkillSticker에서의 name  ";"로 구분되어 여러개입력 
	    [ProtoMember(21, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [is_deleted]  
	    [ProtoMember(22, IsRequired = false)]
		public string date_insert {get; set;} 	// SYSTEMTIME [등록시간] 최초게임등록일 
	    [ProtoMember(23, IsRequired = false)]
		public string date_update {get; set;} 	// SYSTEMTIME [수정된시간] 마지막수정시간 
	    [ProtoMember(24, IsRequired = false)]
		public int elo_point {get; set;} 	// int [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
	    [ProtoMember(25, IsRequired = false)]
		public long team {get; set;} 	// Tbl_Team_id_t [소속팀id] 소속된 팀번호 
	    [ProtoMember(26, IsRequired = false)]
		public int batting_average {get; set;} 	// int16 [타율] 0.001~0.999 천분율로 표시 
	    [ProtoMember(27, IsRequired = false)]
		public int continue_homerun_count {get; set;} 	// int16 [연속홈런수] 연속_홈런수 
	    [ProtoMember(28, IsRequired = false)]
		public int homeruntotal_count {get; set;} 	// int16 [총_홈런수] 총_홈런수 
	    [ProtoMember(29, IsRequired = false)]
		public int single_homerun_count {get; set;} 	// int16 [싱글홈런카운트] 싱글홈런 카운트 
	    [ProtoMember(30, IsRequired = false)]
		public int tworun_homerun_count {get; set;} 	// int16 [더블홈런카운트] 더블홈런 카운트 
	    [ProtoMember(31, IsRequired = false)]
		public int threerun_homerun_count {get; set;} 	// int16 [쓰리런홈런카운트] 쓰리런홈런 카운트 
	    [ProtoMember(32, IsRequired = false)]
		public int grandslam_homerun_count {get; set;} 	// int16 [만루홈런카운트] 만루홈런 카운트 
	    [ProtoMember(33, IsRequired = false)]
		public int one_hit_count {get; set;} 	// int16 [일루타카운트] 일루타 카운트 
	    [ProtoMember(34, IsRequired = false)]
		public int double_hit_count {get; set;} 	// int16 [이루타카운트] 이루타 카운트 
	    [ProtoMember(35, IsRequired = false)]
		public int triple_hit_count {get; set;} 	// int16 [삼루타카운트] 삼루타 카운트 
	    [ProtoMember(36, IsRequired = false)]
		public int foul_hit_count {get; set;} 	// int16 [파울카운트] 파울 카운트 
	    [ProtoMember(37, IsRequired = false)]
		public int out_hit_count {get; set;} 	// int16 [아웃카운트] 아웃 카운트 
	    [ProtoMember(38, IsRequired = false)]
		public int score_count {get; set;} 	// int16 [점수카운트] 점수 카운트 
	    [ProtoMember(39, IsRequired = false)]
		public int betting_type {get; set;} 	// EBetterAbility [타자타입] 타자 대투수 스킬 
	    [ProtoMember(40, IsRequired = false)]
		public int betting_form {get; set;} 	// EBetterForm [타격폼] 타자 폼 
	    [ProtoMember(41, IsRequired = false)]
		public int better_power {get; set;} 	// int16 [타자 파워]  
	    [ProtoMember(42, IsRequired = false)]
		public int better_focus {get; set;} 	// int16 [타자 집중]  
	    [ProtoMember(43, IsRequired = false)]
		public int better_power_buff {get; set;} 	// int16 [타자 파워 버프]  
	    [ProtoMember(44, IsRequired = false)]
		public int better_focus_buff {get; set;} 	// int16 [타자 집중 버프]  
    }//massage s_tbl_playerbetter



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_playerpitcher
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl__PlayerBase_id_t [PK index] 선수 database table PK 
	    [ProtoMember(2, IsRequired = false)]
		public int sid {get; set;} 	// Sys_PlayerCard_id_t [Sys_Player아이디] 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 
	    [ProtoMember(3, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [유저번호]  
	    [ProtoMember(4, IsRequired = false)]
		public string pname {get; set;} 	// aname32_t [닉네임]  
	    [ProtoMember(5, IsRequired = false)]
		public int city {get; set;} 	// EPlayerNationType [출신국가] 캐주얼야구 게임기획서 3차 (20111031).docx참조 
	    [ProtoMember(6, IsRequired = false)]
		public string initial_name {get; set;} 	// aname32_t [이니셜] 생성시 세팅. 등뒤의이니셜글자. 중복가능 
	    [ProtoMember(7, IsRequired = false)]
		public int back_number {get; set;} 	// int16 [백넘버] 생성시 세팅. 변경아이템으로 변경가능 
	    [ProtoMember(8, IsRequired = false)]
		public int age {get; set;} 	// int16 [나이] 생성시 세팅. 
	    [ProtoMember(9, IsRequired = false)]
		public int body_type {get; set;} 	// EPlayerBodyType [체형]  
	    [ProtoMember(10, IsRequired = false)]
		public bool is_left {get; set;} 	// bool [좌우타입] 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 
	    [ProtoMember(11, IsRequired = false)]
		public long exp {get; set;} 	// long [경험치] 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 
	    [ProtoMember(12, IsRequired = false)]
		public int questcomplete_count {get; set;} 	// Sys_Quest_id_t [퀘스트완료_카운트] 완료 퀘스트 카운트 
	    [ProtoMember(13, IsRequired = false)]
		public int win_continue {get; set;} 	// int16 [연승] 연속으로 승리한 개수 
	    [ProtoMember(14, IsRequired = false)]
		public int lose_continue {get; set;} 	// int16 [연패] 연속 패한 개수 
	    [ProtoMember(15, IsRequired = false)]
		public long last_game_result {get; set;} 	// Tbl_Result_id_t [마지막경기id] 마지막으로 플레이한 경기결과 식별자 
	    [ProtoMember(16, IsRequired = false)]
		public int win_tot {get; set;} 	// int [총전적_승] 토탈 승 카운트 
	    [ProtoMember(17, IsRequired = false)]
		public int lose_tot {get; set;} 	// int [총전적_패] 토탈 패 카운트 
	    [ProtoMember(18, IsRequired = false)]
		public int win_season {get; set;} 	// int [시즌전적_승] 시즌 승 카운트(3개월) 
	    [ProtoMember(19, IsRequired = false)]
		public int lose_season {get; set;} 	// int [시즌전적_패] 시즌 패 카운트(3개월) 
	    [ProtoMember(20, IsRequired = false)]
		public string skill_sticker {get; set;} 	// aname1024_t [특수능력이름] Sys_PlayeSkillSticker에서의 name  ";"로 구분되어 여러개입력 
	    [ProtoMember(21, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [is_deleted]  
	    [ProtoMember(22, IsRequired = false)]
		public string date_insert {get; set;} 	// SYSTEMTIME [등록시간] 최초게임등록일 
	    [ProtoMember(23, IsRequired = false)]
		public string date_update {get; set;} 	// SYSTEMTIME [수정된시간] 마지막수정시간 
	    [ProtoMember(24, IsRequired = false)]
		public int elo_point {get; set;} 	// int [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
	    [ProtoMember(25, IsRequired = false)]
		public long team {get; set;} 	// Tbl_Team_id_t [소속팀id] 소속된 팀번호 
	    [ProtoMember(26, IsRequired = false)]
		public int pitching_average {get; set;} 	// int16 [방어율] 0.001~0.999 천분율로 표시 
	    [ProtoMember(27, IsRequired = false)]
		public int hit_count {get; set;} 	// int16 [피안타율] 피안타율 
	    [ProtoMember(28, IsRequired = false)]
		public int strikeout_count {get; set;} 	// int16 [탈삼진수] 탈삼진수 
	    [ProtoMember(29, IsRequired = false)]
		public int homerun_pitching_count {get; set;} 	// int16 [피홈런수] 피홈런수 
	    [ProtoMember(30, IsRequired = false)]
		public int continue_strikeout_count {get; set;} 	// int16 [연속삼진수] 연속삼진수 
	    [ProtoMember(31, IsRequired = false)]
		public int continue_homerun_pitching_count {get; set;} 	// int16 [연속피홈런수] 연속피홈런수 
	    [ProtoMember(32, IsRequired = false)]
		public int pitcher_type {get; set;} 	// EPitcherAbility [투수타입] 투수 대타자 스킬 
	    [ProtoMember(33, IsRequired = false)]
		public int pitcher_form {get; set;} 	// EPitcherForm [투구폼] 투수 폼 
	    [ProtoMember(34, IsRequired = false)]
		public int pitcher_control {get; set;} 	// int16 [투수 제구]  
	    [ProtoMember(35, IsRequired = false)]
		public int pitcher_ballspeed {get; set;} 	// int16 [투수 구속]  
	    [ProtoMember(36, IsRequired = false)]
		public int pitcher_control_buff {get; set;} 	// int16 [투수 제구 버프]  
	    [ProtoMember(37, IsRequired = false)]
		public int pitcher_ballspeed_buff {get; set;} 	// int16 [투수 구속 버프]  
	    [ProtoMember(38, IsRequired = false)]
		public int pitcher_breakingball_value_buff {get; set;} 	// int16 [투수 변화구 수치 버프]  
    }//massage s_tbl_playerpitcher



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_result
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_Result_id_t [game고유번호]  
	    [ProtoMember(2, IsRequired = false)]
		public bool is_singlemode {get; set;} 	// bool [is_singlemode] 0=멀티플레이 1=싱글플레이 
	    [ProtoMember(3, IsRequired = false)]
		public long win_uid {get; set;} 	// Tbl_User_id_t [고유번호] 승자 고유번호 
	    [ProtoMember(4, IsRequired = false)]
		public long win_better {get; set;} 	// Tbl_PlayerBetter_id_t [타자 pid] 승자 
	    [ProtoMember(5, IsRequired = false)]
		public long win_pitcher {get; set;} 	// Tbl_PlayerPitcher_id_t [투수 pid] 승자 
	    [ProtoMember(6, IsRequired = false)]
		public long win_team {get; set;} 	// Tbl_Team_id_t [팀id]  
	    [ProtoMember(7, IsRequired = false)]
		public int win_score {get; set;} 	// int8 [승자스코어]  
	    [ProtoMember(8, IsRequired = false)]
		public int win_reward_exp {get; set;} 	// int [승자 보상경험치] 플레이어1의 보상경험치 
	    [ProtoMember(9, IsRequired = false)]
		public int win_reward_gamemoney {get; set;} 	// game_money_t [승자 보상게임머니] 보상게임머니 
	    [ProtoMember(10, IsRequired = false)]
		public long lose_uid {get; set;} 	// Tbl_User_id_t [고유번호] 패자 고유번호 
	    [ProtoMember(11, IsRequired = false)]
		public long lose_better {get; set;} 	// Tbl_PlayerBetter_id_t [타자 pid] 패자 
	    [ProtoMember(12, IsRequired = false)]
		public long lose_pitcher {get; set;} 	// Tbl_PlayerPitcher_id_t [투수 pid] 패자 
	    [ProtoMember(13, IsRequired = false)]
		public long lose_team {get; set;} 	// Tbl_Team_id_t [패자팀id]  
	    [ProtoMember(14, IsRequired = false)]
		public int lose_score {get; set;} 	// int8 [패자스코어]  
	    [ProtoMember(15, IsRequired = false)]
		public int lose_reward_exp {get; set;} 	// int [패자 보상경험치] 보상경험치 
	    [ProtoMember(16, IsRequired = false)]
		public int lose_reward_gamemoney {get; set;} 	// game_money_t [패자 보상게임머니] 보상게임머니 
	    [ProtoMember(17, IsRequired = false)]
		public string time_start {get; set;} 	// SYSTEMTIME [게임시작시간] 시작 일시 
	    [ProtoMember(18, IsRequired = false)]
		public string time_end {get; set;} 	// SYSTEMTIME [게임종료시간] 플레이 시간 
    }//massage s_tbl_result



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_roundresult
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_RoundResult_id_t [고유번호] 일별 파티션 키 
	    [ProtoMember(2, IsRequired = false)]
		public long grid {get; set;} 	// Tbl_Result_id_t [Tbl_Result_M의 고유번호]  
	    [ProtoMember(3, IsRequired = false)]
		public int round_number {get; set;} 	// int8 [라운드번호] 1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 
	    [ProtoMember(4, IsRequired = false)]
		public long uid_attack {get; set;} 	// Tbl_User_id_t [uid_attack] 공격자 
	    [ProtoMember(5, IsRequired = false)]
		public int score {get; set;} 	// int8 [better의점수]  
	    [ProtoMember(6, IsRequired = false)]
		public int base_runner_state {get; set;} 	// int8 [출루한주자수] bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다 
	    [ProtoMember(7, IsRequired = false)]
		public int hit_type {get; set;} 	// EBetterHitType [안타종류] 0=아웃 1일루타 2이루타 3삼루타 4싱글홈런 5더블홈런 6 
    }//massage s_tbl_roundresult



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_team
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_Team_id_t [고유번호]  
	    [ProtoMember(2, IsRequired = false)]
		public string name {get; set;} 	// aname32_t [팀이름] 디펄트명은 pp_name이다 
	    [ProtoMember(3, IsRequired = false)]
		public long uid {get; set;} 	// Tbl_User_id_t [유저id]  
	    [ProtoMember(4, IsRequired = false)]
		public long pid_better {get; set;} 	// Tbl_PlayerBetter_id_t [타자]  
	    [ProtoMember(5, IsRequired = false)]
		public long pid_pitcher {get; set;} 	// Tbl_PlayerPitcher_id_t [투수]  
	    [ProtoMember(6, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
	    [ProtoMember(7, IsRequired = false)]
		public int win {get; set;} 	// int16 [승]  
	    [ProtoMember(8, IsRequired = false)]
		public int lose {get; set;} 	// int16 [패]  
    }//massage s_tbl_team



    // -------------------------------------------------
    // 설명없음
    // -------------------------------------------------

    [ProtoContract] 
	public class s_tbl_user
    {
	    [ProtoMember(1, IsRequired = false)]
		public long db_id {get; set;} 	// Tbl_User_id_t [고유번호] db pk 피망에서 온 id를 그대로 사용 
	    [ProtoMember(2, IsRequired = false)]
		public string uname {get; set;} 	// aname32_t [닉네임] 베이스볼에서의 유저닉네임 
	    [ProtoMember(3, IsRequired = false)]
		public int tot_win {get; set;} 	// int16 [총전적_승] 투수총전적_승 
	    [ProtoMember(4, IsRequired = false)]
		public int tot_lose {get; set;} 	// int16 [총전적_패] 투수총전적_패 
	    [ProtoMember(5, IsRequired = false)]
		public int pitcher_tot_strikeout {get; set;} 	// int16 [탈삼진수] 투수총_탈삼진 
	    [ProtoMember(6, IsRequired = false)]
		public int pitcher_tot_average_level {get; set;} 	// int16 [투수총평균_레벨] 투수총평균_레벨 멀로 평균을 낼것인가 
	    [ProtoMember(7, IsRequired = false)]
		public int better_tot_homerun {get; set;} 	// int16 [총_홈런수] 타자총_홈런 
	    [ProtoMember(8, IsRequired = false)]
		public int better_tot__average_level {get; set;} 	// int16 [타자총평균_레벨] 타자총평균_레벨 
	    [ProtoMember(9, IsRequired = false)]
		public int cash_item_buy_count {get; set;} 	// int16 [캐쉬템구매갯수] 캐쉬템구매갯수 
	    [ProtoMember(10, IsRequired = false)]
		public string time_last_login {get; set;} 	// SYSTEMTIME [마지막로긴시간] 마지막로긴시간 
	    [ProtoMember(11, IsRequired = false)]
		public string time_last_logout {get; set;} 	// SYSTEMTIME [마지막로그아웃시간] 마지막 로그아웃시간 
	    [ProtoMember(12, IsRequired = false)]
		public int day_continue_attend {get; set;} 	// int16 [연속출석일수] 연속출석한 일수 
	    [ProtoMember(13, IsRequired = false)]
		public string date_insert {get; set;} 	// SYSTEMTIME [등록시간] 최초게임등록일 
	    [ProtoMember(14, IsRequired = false)]
		public string date_update {get; set;} 	// SYSTEMTIME [수정된시간] 마지막수정시간 
	    [ProtoMember(15, IsRequired = false)]
		public long default_tid {get; set;} 	// Tbl_Team_id_t [기본팀번호] 기본팀 index 
	    [ProtoMember(16, IsRequired = false)]
		public string option {get; set;} 	// aname256_t [옵션] 옵션(클라에서임의로저장할내용) 
	    [ProtoMember(17, IsRequired = false)]
		public int is_deleted {get; set;} 	// int16 [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
	    [ProtoMember(18, IsRequired = false)]
		public long game_money {get; set;} 	// long [게임머니]  
	    [ProtoMember(19, IsRequired = false)]
		public long playtime_tot {get; set;} 	// long [총_플레이_타임] 총_플레이_타임(분) 
    }//massage s_tbl_user
}
