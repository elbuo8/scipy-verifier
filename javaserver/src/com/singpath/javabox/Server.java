package com.singpath.javabox;

import com.singpath.javabox.core.PoolController;
import com.singpath.javabox.core.PooledServer;
import com.singpath.javabox.core.QueueLoop;
import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;

public class Server {
	
	public static void main(String[] args){
		
		Logger.getRootLogger().setLevel(Level.INFO);
		BasicConfigurator.configure();
		PoolController controller = new PoolController(10);
		PooledServer   server 	  = new PooledServer(2012,controller);
		QueueLoop      QLoop      = new QueueLoop(controller);
		server.start();
		QLoop.start();
	
	}

}
