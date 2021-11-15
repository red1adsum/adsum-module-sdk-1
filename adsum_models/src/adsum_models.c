/* adsum_models.c  */
/*
 *  * Adsum Networks 2021
 *  KeepAlive and Perfermance Models Library 
 */

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>
#include "adsum_models.h"

#include "adsum_lib.h"


/* * Adsum KeepAlive Model Func * */

void ADSUM_KEEPALIVE_handler(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx, struct net_buf_simple *buf)
{	
	uint16_t peer_addr = ctx->addr ;
	int8_t RSSI = ctx->recv_rssi  ;

	ka_handler(peer_addr,adsum_element_addr, CONFIG_ADSUM_KEEPALIVE_MODEL_SIGN,ctx->recv_ttl,&ADSUM_KEEPALIVE_MODEL_PerfNode_TTL, 
				CONFIG_ADSUM_KEEPALIVE_MODEL_RECEIVED_TTL, CONFIG_ADSUM_KEEPALIVE_MODEL_PERFNODE_SIGN,buf->data,buf->len,2, //Kconfig
				RSSI,addrs_RSSI_list,&idx_n_addrs,&max_recv_TTL);
}

int ADSUM_KEEPALIVE_MSG_publish(struct bt_mesh_model  *model) 
{

	return ka_pub(model,CONFIG_ADSUM_KEEPALIVE_MODEL_PUBLISH_TTL,ADSUM_KEEPALIVE_MODEL_PUB_PERIOD,
				ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT,ADSUM_OP_KEEPALIVE_MSG,CONFIG_ADSUM_KEEPALIVE_MODEL_SIGN);
}

int ADSUM_KEEPALIVE_MODEL_update (struct bt_mesh_model *model){

	
	#ifdef Enable_Printing
	printk("\n - - ADSUM_KEEPALIVE_MODEL_update - -\n");
	#endif
	// update PERF_SRV_MODEL_PUBLISH_TTL
	update_perf_svr_pub_ttl(&ADSUM_PERF_SRV_MODEL_PUBLISH_TTL,&ADSUM_KEEPALIVE_MODEL_PerfNode_TTL,&max_recv_TTL);

	return update_ka_pub_params(model,CONFIG_ADSUM_KEEPALIVE_MODEL_PUBLISH_TTL,ADSUM_KEEPALIVE_MODEL_PUB_PERIOD,ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT); 
}

int ADSUM_KEEPALIVE_MODEL_init(struct bt_mesh_model *model){
	#ifdef Enable_Printing
	printk("- ADSUM_KEEPALIVE_MODEL_init - \n");
	#endif
	
	struct bt_mesh_adsum_keepalive_model_context *adsum_keepalive_model = model->user_data;

	adsum_keepalive_model->model = model;

	net_buf_simple_init_with_data(&adsum_keepalive_model->pub_msg, adsum_keepalive_model->buf,sizeof(adsum_keepalive_model->buf));
	adsum_keepalive_model->pub.msg = &adsum_keepalive_model->pub_msg;
	adsum_keepalive_model->pub.update = ADSUM_KEEPALIVE_MODEL_update;

	adsum_keepalive_model->pub.period = ADSUM_KEEPALIVE_MODEL_PUB_PERIOD ; 
	adsum_keepalive_model->pub.addr = CONFIG_ADSUM_KEEPALIVE_GROUP_ADDR ;
	adsum_keepalive_model->pub.retransmit = ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT ;

	return 0;
}

int ADSUM_KEEPALIVE_MODEL_start(struct bt_mesh_model *model){
	
	#ifdef Enable_Printing
	printk("- ADSUM_KEEPALIVE_MODEL_start - \n");
	#endif
	//period and group addrs and retransm set in init
	model->pub->ttl = CONFIG_ADSUM_KEEPALIVE_MODEL_PUBLISH_TTL ;
	model->groups[0] = CONFIG_ADSUM_KEEPALIVE_GROUP_ADDR;
	get_adsum_element_addr(); 
	int err = ADSUM_KEEPALIVE_MSG_publish(model);
	#ifdef Enable_Printing
	printk("ADSUM_KEEPALIVE_MSG_publish return:%d\n", err);
	#endif
	
	return 0;
}

const struct bt_mesh_model_cb ADSUM_KEEPALIVE_MODEL_callbacks ={ //#
	.init=ADSUM_KEEPALIVE_MODEL_init,
	.start = ADSUM_KEEPALIVE_MODEL_start,
};

/* * ADSUM_PERF Model Func * */
int ADSUM_PERF_SRV_publish(struct bt_mesh_model  *model){

	return pn_pub(model,ADSUM_PERF_SRV_MODEL_PUBLISH_TTL,ADSUM_PERF_SRV_MODEL_PUB_PERIOD,ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT,ADSUM_OP_PERF_UPDATE,CONFIG_ADSUM_PERF_SRV_MODEL_SIGN);
}

int ADSUM_PERF_SRV_MODEL_init(struct bt_mesh_model *model){
	
	#ifdef Enable_Printing
	printk("- ADSUM_PERF_SRV_MODEL_init - \n");
	#endif

	struct bt_mesh_adsum_perf_srv_model_context  *adsum_perf_srv_model = model->user_data;

	adsum_perf_srv_model->model = model;

	net_buf_simple_init_with_data(&adsum_perf_srv_model->pub_msg, adsum_perf_srv_model->buf,sizeof(adsum_perf_srv_model->buf));
	adsum_perf_srv_model->pub.msg = &adsum_perf_srv_model->pub_msg;
	adsum_perf_srv_model->pub.update = ADSUM_PERF_SRV_MODEL_update;

	adsum_perf_srv_model->pub.period = ADSUM_PERF_SRV_MODEL_PUB_PERIOD ; 
	adsum_perf_srv_model->pub.addr = CONFIG_ADSUM_PERF_GROUP_ADDR ;
	adsum_perf_srv_model->pub.retransmit = ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT ;
	
	return 0;
}

int ADSUM_PERF_SRV_MODEL_start(struct bt_mesh_model *model){
	
	#ifdef Enable_Printing
	printk("- ADSUM_PERF_SRV_MODEL_start - \n");
	#endif

	model->pub->ttl = ADSUM_PERF_SRV_MODEL_PUBLISH_TTL ;
	int err = ADSUM_PERF_SRV_publish(model);
	#ifdef Enable_Printing
	printk("ADSUM_PERF_SRV_publish return:%d\n", err); 
	#endif
	return 0;
}

int ADSUM_PERF_SRV_MODEL_update (struct bt_mesh_model *model){

	// it should return
	return pn_update(model,ADSUM_PERF_SRV_MODEL_PUBLISH_TTL,ADSUM_PERF_SRV_MODEL_PUB_PERIOD, ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT,
				ADSUM_OP_PERF_UPDATE,&idx_n_addrs, addrs_RSSI_list ,net_comp);
				

}
const struct bt_mesh_model_cb ADSUM_PERF_SRV_MODEL_callbacks ={ //#
	.init = ADSUM_PERF_SRV_MODEL_init,
	.start = ADSUM_PERF_SRV_MODEL_start,
};

// Opcodes list
const struct bt_mesh_model_op ADSUM_KEEPALIVE_MODEL_OPS[] = {
	{ ADSUM_OP_KEEPALIVE_MSG, 0, ADSUM_KEEPALIVE_handler },
	BT_MESH_MODEL_OP_END,
};
const struct bt_mesh_model_op ADSUM_PERF_SVR_MODEL_OPS[] = {
	{ ADSUM_OP_PERF_UPDATE, 0, NULL},
	BT_MESH_MODEL_OP_END,
};

// adsum models init
void adsum_model_init(const struct bt_mesh_comp *comp){
	net_comp = comp; 
	get_adsum_element_addr();//-
	#ifdef Enable_Printing
	#endif
	// comp print
	#ifdef Enable_Printing
	printk(" - - - - - Composition - - - - -\n ");
	#endif
		uint16_t company_cid = net_comp->cid;
		#ifdef Enable_Printing
		printk("company_cid:%04x \n ",company_cid);
		#endif
		uint8_t elements_number = net_comp->elem_count;
		#ifdef Enable_Printing
		printk("Elements number: %d \n",elements_number);
		#endif
		for (size_t i = 0; i < elements_number; i++)
		{
			uint16_t element_i_addr = net_comp->elem[i].addr;
			#ifdef Enable_Printing
			printk("  -Element%d: unicast=%04x \n",i,element_i_addr);
			#endif
			
			uint8_t sig_models_count=net_comp->elem[i].model_count;
			#ifdef Enable_Printing
			printk("      * SIG Model number: %d \n",sig_models_count);
			#endif
			
			for (uint8_t j = 0; j < sig_models_count; j++)
			{
				uint16_t sig_model_id=net_comp->elem[i].models[j].id;
				#ifdef Enable_Printing
				printk("         id(%04x) \n",sig_model_id);
				#endif
			}
			
			uint8_t vnd_models_count =net_comp->elem[i].vnd_model_count;
			#ifdef Enable_Printing
			printk("      * Vender Model number: %d \n",vnd_models_count);
			#endif
			
			for (uint8_t j = 0; j < vnd_models_count; j++)
			{
				uint16_t vnd_model_company_id =net_comp->elem[i].vnd_models[j].vnd.company; 
				uint16_t vnd_model_id =net_comp->elem[i].vnd_models[j].vnd.id;
				#ifdef Enable_Printing
				printk("         id(%04x%04x) \n",vnd_model_company_id,vnd_model_id);
				#endif
			}
		}
}

void get_adsum_element_addr(){
	#ifdef Enable_Printing
	#endif
	#ifdef Enable_Printing
	printk("- - get_adsum_element_addr - - \n");
	#endif
	if(net_comp != NULL){
		bool adsum_element_addr_is_set=0; 
		for (uint8_t i = 0; i < net_comp->elem_count; i++)
		{
			if(net_comp->elem[i].loc == 77 ){
				adsum_element_addr = net_comp->elem[i].addr;
				#ifdef Enable_Printing
				printk("adsum_element_addr= %04x : found in %d\n",adsum_element_addr,i);
				#endif
				adsum_element_addr_is_set=1;
			}
		}
		if(!adsum_element_addr_is_set){
			#ifdef Enable_Printing
			printk("ERROR: adsum_element_addr is not set [X] \n");
			#endif
		}
	}else {
		#ifdef Enable_Printing
		printk("net_comp not pointed correctly\n");
		#endif
	}	
}

   
   