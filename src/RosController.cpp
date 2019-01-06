#include "RosController.h"

RosController::RosController() 
{
    init_();
}


RosController::RosController(IPAddress * server, uint16_t server_port)
{
    #if defined(ESP8266)
    nh.getHardware()->setConnection(*server, server_port);
    #endif

    init_();
}

void RosController::init_()
{    
    #if not defined(ESP8266)
    nh.getHardware()->setBaud(115200);
    #endif

    nh.initNode();
    broadcaster.init(nh);

    current_time_ = last_time_ = nh.now();   
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
        
        current_time_ = nh.now();
        double dt = current_time_.toSec() - last_time_.toSec();   

        for(int i=0;i<ros_nodes.size();i++) 
        {
            ros_nodes[i]->update(current_time_,broadcaster);
        }

        last_time_ = current_time_;
        
        nh.spinOnce(); 
        //Delay
        delay(100);  
    }    
}
