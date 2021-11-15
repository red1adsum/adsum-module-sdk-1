/* adsum_models.h  */
/*
 *  * Adsum Networks 2021
 *  KeepAlive and Perfermance Models Library 
 */
#ifndef BT_MESH_ADSUM_MODELS_H__
#define BT_MESH_ADSUM_MODELS_H__

#define Enable_Printing 

#define ADSUM_KEEPALIVE_MODEL_PUB_PERIOD BT_MESH_PUB_PERIOD_10SEC(CONFIG_ADSUM_KEEPALIVE_MODEL_PUB_PERIOD_10S_MULTIPLIER)  
#define ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT BT_MESH_PUB_TRANSMIT(CONFIG_ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT_NMBR, CONFIG_ADSUM_KEEPALIVE_MODEL_PUB_RETRANSMIT_INTER)
#define ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT BT_MESH_PUB_TRANSMIT(CONFIG_ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT_NMBR,CONFIG_ADSUM_PERF_SRV_MODEL_PUB_RETRANSMIT_INTER)
#define ADSUM_PERF_SRV_MODEL_PUB_PERIOD BT_MESH_PUB_PERIOD_10SEC(CONFIG_ADSUM_PERF_SRV_MODEL_PUB_PERIOD_10S_MULTIPLIER) 

// Neighbours list
struct Addrs_RSSI_List  {
	uint16_t n_addrs;
	int8_t n_RSSI;
	uint8_t RSSIs_idx;
};
static struct Addrs_RSSI_List addrs_RSSI_list[CONFIG_ADSUM_ADDRS_RSSI_LIST_SIZE] ;

/* global variables */

static uint16_t adsum_element_addr; //#

static uint8_t idx_n_addrs = 0;
// Dynamic TTL 
static uint8_t max_recv_TTL = 0; //changed int16_t
static int8_t ADSUM_KEEPALIVE_MODEL_PerfNode_TTL=-1; //Todo -1  (max 127)

static uint8_t ADSUM_PERF_SRV_MODEL_PUBLISH_TTL = 0; //TBD 

// Functions and callbacks
int ADSUM_KEEPALIVE_MODEL_update (struct bt_mesh_model *model);
int ADSUM_KEEPALIVE_MSG_publish(struct bt_mesh_model  *model);
void ADSUM_KEEPALIVE_handler(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx, struct net_buf_simple *buf);
int ADSUM_KEEPALIVE_MODEL_init(struct bt_mesh_model *model);
int ADSUM_KEEPALIVE_MODEL_start(struct bt_mesh_model *model);
// Functions and callbacks
int ADSUM_PERF_SRV_MODEL_update (struct bt_mesh_model *model) ;
int ADSUM_PERF_SRV_publish(struct bt_mesh_model  *model);
int ADSUM_PERF_SRV_MODEL_init(struct bt_mesh_model *model);
int ADSUM_PERF_SRV_MODEL_start(struct bt_mesh_model *model);
//

static const struct bt_mesh_comp *net_comp; 
void get_adsum_element_addr();


/** Internal utility macro for type checking model user data.
 *
 * Produces a "Comparison of distinct pointer types" warning if @p _user_data
 * is of the wrong type.
 * */
#define BT_MESH_MODEL_USER_DATA(_type, _user_data)                             \
	(((_user_data) == (_type *)0) ? NULL : (_user_data))
#define ADSUM_OP_KEEPALIVE_MSG BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_KEEPALIVE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 

struct bt_mesh_adsum_keepalive_model_context ;
#define BT_MESH_ADSUM_KEEPALIVE_MODEL(_keepalive_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_KEEPALIVE_MODEL_ID,                      \
			ADSUM_KEEPALIVE_MODEL_OPS, &(_keepalive_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_keepalive_model_context,       \
						_keepalive_model),                        \
			&ADSUM_KEEPALIVE_MODEL_callbacks)

// ADSUM KeepAlive Model  context.
struct bt_mesh_adsum_keepalive_model_context {
	// ** Access model pointer. * /
	struct bt_mesh_model *model;
	// ** Publish parameters. * /
	struct bt_mesh_model_pub pub;
	// ** Publication message. * /
	struct net_buf_simple pub_msg;
	// ** Publication message buffer. * /
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_KEEPALIVE_MSG,CONFIG_ADSUM_OP_KEEPALIVE_MSG_MAXLEN_MESSAGE)];
};


/* * =	=	=	=	=	=	=	=	= ADSUM PERFORMANCE SERVER : MODEL =	=	=	=	=	=	=	=	= * */ //
#define ADSUM_OP_PERF_UPDATE BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_PERF_UPDATE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 

struct bt_mesh_adsum_perf_srv_model_context ;
#define BT_MESH_ADSUM_PERF_SRV_MODEL(_perf_srv_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_PERF_SRV_MODEL_ID,                      \
			ADSUM_PERF_SVR_MODEL_OPS, &(_perf_srv_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_perf_srv_model_context,       \
						_perf_srv_model),                        \
			&ADSUM_PERF_SRV_MODEL_callbacks)

// ADSUM Perf Server Model  context.
struct bt_mesh_adsum_perf_srv_model_context {
	// ** Access model pointer. * /
	struct bt_mesh_model *model;
	// ** Publish parameters. * /
	struct bt_mesh_model_pub pub;
	// ** Publication message. * /
	struct net_buf_simple pub_msg;
	// ** Publication message buffer. * /
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_PERF_UPDATE,CONFIG_ADSUM_OP_PERF_UPDATE_MAXLEN_MESSAGE)];
};


// adsum models init 
void adsum_model_init(const struct bt_mesh_comp *comp);

// Externals
extern const struct bt_mesh_model_cb ADSUM_KEEPALIVE_MODEL_callbacks;
extern const struct bt_mesh_model_cb ADSUM_PERF_SRV_MODEL_callbacks;

extern const struct bt_mesh_model_op ADSUM_KEEPALIVE_MODEL_OPS[] ;
extern const struct bt_mesh_model_op ADSUM_PERF_SVR_MODEL_OPS[] ;

static struct bt_mesh_adsum_keepalive_model_context adsum_keepalive_model ;
static struct bt_mesh_adsum_perf_srv_model_context adsum_perf_srv_model ;
static struct bt_mesh_model Adsum_models[] = {
	BT_MESH_ADSUM_KEEPALIVE_MODEL(&adsum_keepalive_model),
	BT_MESH_ADSUM_PERF_SRV_MODEL(&adsum_perf_srv_model)
};

#endif /* BT_MESH_ADSUM_MODELS_H__ */