
#ifndef ZERG_SERVER_AUTO_CONNECT_H_
#define ZERG_SERVER_AUTO_CONNECT_H_



class Zerg_Server_Config;



/****************************************************************************************************
class Zerg_Auto_Connector
****************************************************************************************************/
class Zerg_Auto_Connector
{

public:

    //���캯��
    Zerg_Auto_Connector();
    ~Zerg_Auto_Connector();

    //
    int get_config(const Zerg_Server_Config *config);

    // ���¼���������������
    int reload_cfg(const Zerg_Server_Config *config);


    /*!
    * @brief      �������еķ�����,����Ѿ������ӣ�������,
    * @return     void
    * @param      szvalid  ��Ȼ��Ч�ĵ�����
    * @param      sz_succ  �ɹ���ʼ���ӵķ���������
    * @param      szfail   ����ʧ�ܵķ����������������������첽���ӣ�����ط�����һ�����ǽ���������
    * @note
    */
    void reconnect_allserver(size_t &szvalid, size_t &sz_succ, size_t &szfail);


    //���ӵ�����
    size_t numsvr_connect();


    /*!
    * @brief      ����SVC ID,����Ƿ����������ӵķ���.,
    * @return     int
    * @param      reconnect_svcid Ҫ������������·����Ϣ
    * @note       Ϊʲô����һ��TCP_Svc_Handler��Ϊ��������,��Ϊ�ڷ���Connect������,Ҳ����handle_close.
    */
    int reconnect_server(const SERVICES_ID &reconnect_svcid);


    /*!
    * @brief      ����services_type��ѯ��Ӧ�����������������б����� MS��������
    * @return     int == 0 ��ʾ�ɹ�
    * @param[in]  services_type
    * @param[out] ms_svcid_ary   ���õ������������б�����
    */
    int find_conf_ms_svcid_ary(uint16_t services_type,
                               std::vector<uint32_t> *& ms_svcid_ary);


    inline bool is_auto_connect_svcid(const SERVICES_ID &svc_id)
    {
        //�����SET�����Ҳ���
        if (set_auto_cnt_svcid_.find(svc_id) == set_auto_cnt_svcid_.end())
        {
            return false;
        }
        return true;
    }
protected:

    //����SVRINFO+IP,����Ƿ����������ӵķ���.����������
    int connect_server_bysvcid(const SERVICES_ID &svc_id,
                               const ZCE_Sockaddr_In &inet_addr);

protected:

    //
    typedef std::vector<SERVICES_INFO > ARRAY_OF_ZERG_SVCINFO;
    //
    typedef std::unordered_set<SERVICES_ID, HASH_OF_SVCID> SET_OF_SVCID;

    ///���Ͷ�Ӧ��SERVICES ID �����MAP������,
    typedef std::unordered_map<uint16_t, std::vector<uint32_t> > MAP_OF_TYPE_TO_IDARY;

protected:

    //������
    ZCE_Socket_Connector zerg_connector_;

    //����ʵ��ָ��
    const Zerg_Server_Config *zerg_svr_cfg_ = NULL;

    ///
    size_t size_of_wantconnect_ = 0;
    ///
    ARRAY_OF_ZERG_SVCINFO    ary_want_connect_;
    ///
    SET_OF_SVCID set_auto_cnt_svcid_;;

    //���Ͷ�Ӧ��SERVICES ID ���� ��MAP�����������id��˳����ʵ������˳��
    MAP_OF_TYPE_TO_IDARY     type_to_idary_map_;

};


#endif //_ZERG_SERVER_AUTO_CONNECT_H_

