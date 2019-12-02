#include "RosController.h"

RosController::RosController() 
{
    init_();
}

#if defined(ESP8266)
RosController::RosController(IPAddress * server, uint16_t server_port)
{
    nh.getHardware()->setConnection(*server, server_port);
    init_();
}
#endif

void RosController::init_()
{    
    #if not defined(ESP8266)
    nh.getHardware()->setBaud(115200);
    #endif

    nh.initNode();
    broadcaster.init(nh);
}

void RosController::init() 
{

    for(int i=0;i<ros_nodes.size();i++) 
    {
        ros_nodes[i]->init(nh);
    }    
}

void RosController::readConfiguration(RosConfigBase * ros_config)
{
    while(!nh.connected()) {nh.spinOnce();}

    if (nh.connected()) {
        ros_config->read(nh);
    }    
}


void RosController::update()
{    
    while(!nh.connected()) {nh.spinOnce();}

    if (nh.connected()) {        
        
        ros::Time current_time = nh.now();

        for(int i=0;i<ros_nodes.size();i++) 
        {
            ros_nodes[i]->update(current_time,broadcaster);
        }
                
        nh.spinOnce(); 
    }    
}
