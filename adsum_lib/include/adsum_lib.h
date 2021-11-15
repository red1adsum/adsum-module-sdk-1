#ifndef BT_MESH_ADSUM_LIB_H__
#define BT_MESH_ADSUM_LIB_H__


struct _Addrs_RSSI_List  {
	uint16_t n_addrs;
	int8_t n_RSSI;
	uint8_t RSSIs_idx;
};


bool is_valid_ka(uint16_t peer_addr,uint16_t adsum_element_addr,uint8_t buf_data_0, uint8_t keepalive_model_sign,uint8_t recv_ttl,uint8_t keepalive_model_recv_ttl,uint8_t keepalive_model_perf_node_sign);

int8_t set_ka_pn_ttl(uint8_t *buf_data,uint8_t keepalive_model_perf_node_sign,uint8_t buf_len,uint8_t msg_len_keepalive_model_perf_node_sign );

void store_addrs_list(uint16_t peer_addr,int8_t RSSI,struct _Addrs_RSSI_List *_Addrs_RSSI_List,uint8_t *idx_n_addrs);

void is_valid_nei(uint8_t buf_data_0,uint8_t keepalive_model_sign,uint8_t keepalive_model_perf_node_sign,uint8_t recv_ttl,uint8_t keepalive_model_perf_node_ttl,
                    uint16_t peer_addr,int8_t RSSI,struct _Addrs_RSSI_List *_Addrs_RSSI_List,uint8_t *idx_n_addrs);

void is_perf_node(uint8_t buf_data_0,uint8_t keepalive_model_perf_node_sign,uint8_t recv_ttl,uint8_t *max_recv_TTL);

void ka_handler(uint16_t peer_addr,uint16_t adsum_element_addr,uint8_t keepalive_model_sign,uint8_t recv_ttl,
				uint8_t *keepalive_model_perf_node_ttl,uint8_t keepalive_model_recv_ttl,uint8_t keepalive_model_perf_node_sign,uint8_t *buf_data,
				uint8_t buf_len,uint8_t msg_len_keepalive_model_perf_node_sign ,
				int8_t RSSI,struct _Addrs_RSSI_List *addrs_RSSI_list,uint8_t *idx_n_addrs,uint8_t *max_recv_TTL);

int ka_pub(struct bt_mesh_model  *model ,uint8_t keepalive_model_pub_ttl,uint8_t keepalive_model_pub_period,
			uint8_t keepalive_model_pub_retransmt,uint32_t op_keepalive_msg,uint8_t keepalive_model_sign);

void update_perf_svr_pub_ttl(uint8_t *ADSUM_PERF_SRV_MODEL_PUBLISH_TTL,int8_t *ADSUM_KEEPALIVE_MODEL_PerfNode_TTL,uint8_t *max_recv_TTL);

int update_ka_pub_params(struct bt_mesh_model  *model,uint8_t keepalive_model_pub_ttl,uint8_t keepalive_model_pub_period,uint8_t keepalive_model_pub_retransmit);


void _get_adsum_element_addr(struct bt_mesh_comp *net_comp, uint16_t *adsum_element_addr);

int pn_pub(struct bt_mesh_model  *model ,uint8_t perf_svr_model_pub_ttl,uint8_t perf_svr_model_pub_period,
			uint8_t perf_svr_model_pub_retransmt,uint32_t op_perf_svr_msg,uint8_t perf_svr_model_sign);

int pn_update(struct bt_mesh_model  *model,uint8_t _ADSUM_PERF_SRV_MODEL_PUBLISH_TTL,uint8_t _ADSUM_PERF_SRV_MODEL_PUB_PERIOD,
				uint8_t _ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT,uint32_t _ADSUM_OP_PERF_UPDATE,uint8_t *idx_n_addrs,
				struct _Addrs_RSSI_List *addrs_RSSI_list ,struct bt_mesh_comp *net_comp);
#endif 