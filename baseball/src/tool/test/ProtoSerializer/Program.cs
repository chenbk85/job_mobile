//using System;
using System.Collections.Generic;
using System.Text;

using ProtoBuf;
using ProtoBuf.Meta;
using nPROTO;
//using nPROTOCOL;

namespace ProtoSerializer
{
    class Program
    {

        static void Main(string[] args)
        {
            
            var model = TypeModel.Create();

            //----------------------------------------------------------------
            //- ug.cs
            model.Add(typeof(nPROTO.Version), true );
            model.Add(typeof(Error), true );
            model.Add(typeof(Desc), true );
            model.Add(typeof(Notice), true );
            model.Add(typeof(UError), true );
            model.Add(typeof(UReqConnect), true );
            model.Add(typeof(UAnsConnect), true );
            model.Add(typeof(UReqNotice), true );
            model.Add(typeof(UAnsNotice), true );
            model.Add(typeof(UReqChannel), true );
            model.Add(typeof(UAnsChannel), true );
            model.Add(typeof(UErrChannel), true );
            model.Add(typeof(UReqStore), true );
            model.Add(typeof(UAnsStore), true );
            model.Add(typeof(UReqInfo), true );
            model.Add(typeof(UAnsInfo), true );
            model.Add(typeof(UReqAutoJoin), true );
            model.Add(typeof(UAnsAutoJoin), true );
            model.Add(typeof(UReqLeaveGame), true );
            model.Add(typeof(UAnsLeaveGame), true );
            model.Add(typeof(UReqClose), true );
            model.Add(typeof(UAnsClose), true );
            model.Add(typeof(UReqPong), true );
            model.Add(typeof(UAnsPing), true );
            model.Add(typeof(UReqPlug), true );
            model.Add(typeof(UAnsPlug), true );
            model.Add(typeof(UReqProtocol), true );
            model.Add(typeof(UAnsProtocol), true );
            model.Add(typeof(MemberInfo), true);

            //----------------------------------------------------------------
            //- db.cs
            model.Add(typeof(DBIn), true);
            model.Add(typeof(ReqDB), true);
            model.Add(typeof(AnsDB), true);

            //----------------------------------------------------------------
            //- excel_baseball_table_db.cs
            model.Add(typeof(s_tbl__playerbase), true);
            model.Add(typeof(s_tbl_friend), true);
            model.Add(typeof(s_tbl_item), true);
            model.Add(typeof(s_tbl_item_admin), true);
            model.Add(typeof(s_tbl_pitcherskill), true);
            model.Add(typeof(s_tbl_playerbetter), true);
            model.Add(typeof(s_tbl_playerpitcher), true);
            model.Add(typeof(s_tbl_result), true);
            model.Add(typeof(s_tbl_roundresult), true);
            model.Add(typeof(s_tbl_team), true);
            model.Add(typeof(s_tbl_user), true);

            //----------------------------------------------------------------
            //- game.cs
            model.Add(typeof(GReqGameEnter), true);
            model.Add(typeof(GAnsGameEnter), true);
            model.Add(typeof(GReqGameLeave), true);
            model.Add(typeof(GAnsGameLeave), true);
            model.Add(typeof(GReqDetach), true);
            model.Add(typeof(GAnsDetach), true);
            model.Add(typeof(GReqPlug), true);
            model.Add(typeof(GAnsPlug), true);
            model.Add(typeof(GError), true);
            model.Add(typeof(GErrPlug), true);
            model.Add(typeof(GAnsUserUpdate), true);
            model.Add(typeof(GAnsStatus), true);
            model.Add(typeof(GReqStatus), true);
            model.Add(typeof(GReqProtocol), true);
            model.Add(typeof(GAnsProtocol), true);

            //----------------------------------------------------------------
            //- gameLogic.cs
            model.Add(typeof(EUserGPS), true);
            model.Add(typeof(GameUserInfo), true);
            model.Add(typeof(GameInfo), true);
            model.Add(typeof(s_game_play_info), true);
            model.Add(typeof(s_result_round), true);
            model.Add(typeof(s_result_game), true);
            model.Add(typeof(GameRoomInfo), true);
            model.Add(typeof(s_vector3), true);
            model.Add(typeof(s_vector2), true);
            model.Add(typeof(s_pitcher_throw_info), true);
            model.Add(typeof(s_pitcher_throw_info_verify), true);
            model.Add(typeof(s_better_hit_info), true);
            model.Add(typeof(s_better_hit_info_verify), true);
            model.Add(typeof(GLReqGameProtocol), true);
            model.Add(typeof(GLAnsGameProtocol), true);

            //----------------------------------------------------------------
            //- presence.cs
            model.Add(typeof(PresenceCommand), true);
            model.Add(typeof(PReqProtocol), true);
            model.Add(typeof(PAnsProtocol), true);

            //----------------------------------------------------------------
            //- protocol.cs
            model.Add(typeof(nPROTOCOL.GameUserInfo), true);
            model.Add(typeof(nPROTOCOL.GameRoomInfo), true);
            model.Add(typeof(nPROTOCOL.GameInfo), true);
            model.Add(typeof(nPROTOCOL.AnsJoinUser), true);
            model.Add(typeof(nPROTOCOL.AnsLeaveUser), true);
            model.Add(typeof(nPROTOCOL.ReqPurgeUser), true);
            model.Add(typeof(nPROTOCOL.GLReqGameProtocol), true);
            model.Add(typeof(nPROTOCOL.GLAnsGameProtocol), true);

            //----------------------------------------------------------------
            //- PT_BaseballServer.cs
            model.Add(typeof(EUserGPS_notuse), true);
            model.Add(typeof(s_req_ping1), true);
            model.Add(typeof(s_ans_pong1), true);
            model.Add(typeof(s_req_chat), true);
            model.Add(typeof(s_ans_chat), true);
            model.Add(typeof(s_ans_timer_start), true);
            model.Add(typeof(s_req_timer_start), true);
            model.Add(typeof(s_req_do_disconnect), true);
            model.Add(typeof(s_req_ping2), true);
            model.Add(typeof(s_ans_pong2), true);
            model.Add(typeof(s_ans_bs_error), true);
            model.Add(typeof(s_req_get_cvar), true);
            model.Add(typeof(s_req_set_cvar), true);
            model.Add(typeof(s_ans_join_room), true);
            model.Add(typeof(s_req_room_state), true);
            model.Add(typeof(s_ans_room_state), true);
            model.Add(typeof(s_req_team_match_ready), true);
            model.Add(typeof(s_ans_team_match_ready), true);
            model.Add(typeof(s_ans_game_start), true);
            model.Add(typeof(s_ans_game_round_start), true);
            model.Add(typeof(s_req_pitcher_throw), true);
            model.Add(typeof(s_ans_pitcher_throw), true);
            model.Add(typeof(s_req_better_hit), true);
            model.Add(typeof(s_ans_better_hit), true);
            model.Add(typeof(s_req_result_better_hit), true);
            model.Add(typeof(s_ans_result_better_hit), true);
            model.Add(typeof(s_ans_change_attack_team), true);
            model.Add(typeof(s_ans_game_end), true);
            model.Add(typeof(s_ans_user_disconnect), true);
            model.Add(typeof(BaseballServer_Client), true);
            model.Add(typeof(Client_BaseballServer), true);

            //----------------------------------------------------------------
            //- PT_UserGateServer.cs
            model.Add(typeof(s_ans_add_item), true);
            model.Add(typeof(s_req_admin_add_item), true);
            model.Add(typeof(s_req_item_buy), true);
            model.Add(typeof(s_req_player_create_better), true);
            model.Add(typeof(s_ans_player_create_better), true);
            model.Add(typeof(s_req_player_delete), true);
            model.Add(typeof(s_ans_player_delete), true);
            model.Add(typeof(s_req_echo_to_ug), true);
            model.Add(typeof(s_ans_echo_from_ug), true);
            model.Add(typeof(s_req_player_create_pitcher), true);
            model.Add(typeof(s_ans_player_create_pitcher), true);
            model.Add(typeof(s_ans_ug_error), true);
            model.Add(typeof(s_req_add_tbl_pitcherskill), true);
            model.Add(typeof(s_ans_add_tbl_pitcherskill), true);
            model.Add(typeof(s_req_team_create), true);
            model.Add(typeof(s_ans_team_create), true);
            model.Add(typeof(s_req_team_delete), true);
            model.Add(typeof(s_ans_team_delete), true);
            model.Add(typeof(s_req_team_select), true);
            model.Add(typeof(s_ans_team_select), true);
            model.Add(typeof(UserGateServer_Client), true);
            model.Add(typeof(Client_UserGateServer), true);

            //----------------------------------------------------------------

            model.Compile("ProtoSerializer", "ProtoSerializer.dll");
        }
    }
}
