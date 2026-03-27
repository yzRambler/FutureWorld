 {
    "Scene": {
        "Name": "HellowWorld",
        "TimeOrder": 0,
        "SceneNode": {
        		"Name": "UserRoot",
        		"SpaceOrder": 0,
        		"SpaceWorld": {
            				"Pos": {"x": 0.0, "y": 0.0, "z": 0.0},
                    "Forward": {"x": 0.0, "y": 0.0, "z": 1.0},
                    "Up": {"x": 0.0, "y": 1.0, "z": 0.0}
            },
            "Children": [
            		{
            				"SceneNode": {
            						"Name": "Main Camera Node",
            						"SpaceOrder": 0,
            						"SpaceWorld": {
            										"Pos": {"x": 0.0, "y": -0.5, "z": 2.5},
                                "Forward": {"x": 0.0, "y": 0.0, "z": 1.0},
                                "Up": {"x": 0.0, "y": 1.0, "z": 0.0}
            						},
            						"Construct": {
            								"Class": "Essety",
                						"Name": "Camera",
                						"Component": [
                								{
                										"Class": "Camera",
            												"Name": "Main Camera",
            												"TargetSpaceOrder": 0,
            												"TargetTimeOrder": 0,
            												"TargetScreenID": 0,
            												"Type": "Perspect",
                		   							"AspectRatio": 1.333,
                		   							"FOV": 60.0,
                		   							"Near": 1.0,
                		   							"Far": 1000.0,
                		   							"ViewPort": {"X": 0.0, "Y": 0.0, "W": 1.0, "H": 1.0},
                		   							"Enable": ["Depth"],
                		   							"ClearColor": { "r": 0.0, "g": 0.0, "b": 0.5, "a": 0.0 },
                		   							"Clear": ["Depth", "Color"]
                								}
                						]
            								
            						}
            				}
            				
            		},
            		{
            				"SceneNode":{
                		    "Name": "Main Direct Light Node",
                		    "SpaceOrder": 0,
                		    "SpaceWorld": {
            										"Pos": {"x": 0.0, "y": 20.0, "z": 0.0},
                                "Forward": {"x": -1.0, "y": 1.0, "z": -1.0},
                                "Up": {"x": 0.0, "y": 1.0, "z": 0.0}
            						},
                		    "Construct":{
                		    		"Class": "Essety",
                						"Name": "Light",
                						"Component": [
                								{
                										"Class": "Light",
                		    						"Name": "Main Light",	
                		    						"TargetSpaceOrder": 0,	
            												"LitType": "Direct",
                            				"Intensity": 1.0,
                            				"Color": {"r": 1.0, "g": 1.0, "b": 1.0, "a": 1.0} 
                								}
                						]
                		    }
            				}

            		},
            		{
            				"SceneNode":{
                				"Name": "DavidHead",
                				"SpaceOrder": 0,
                				"SpaceWorld": {
                                "Pos": {"x": 0.0, "y": 0.0, "z": 0.0},
                                "Forward": {"x": 0.0, "y": 0.0, "z": 1.0},
                                "Up": {"x": 0.0, "y": 1.0, "z": 0.0}
                        },
                				"Construct":{
                						"Class": "Essety",
                						"Name": "DavidHead",
                						"Component": [
                								{
                												"Class": "Render",
                                				"Name": "DavidHeadRender",
                                				"Comesh": {
                                    				"Name": "DavidHeadComesh", 
                                    				"NameFile": "./resources/David/DavidHead.fwd",
                                    				"SpaceModel":{
                                    								 "Pos": {"x": 0.0, "y": 0.0, "z": 0.0},
                                    								 "Forward": {"x": 0.0, "y": -1.0, "z": 0.0},
                                    								 "Up": {"x": 0.0, "y": 1.0, "z": 0.0} 
                                    				},
                                    				"Meshes": [
                                        				{ "Name": "Head",
                                          				"NameFile": "./resources/David/DavidHead.fwd",
                                          				"Material": {
                                             				"Name": "DavidHeadMaterial",
                                             				"NameFile": "./resources/David/DavidHead.mat"
                                             				}
                                        				}
    				
                                    				]
                                				}
                								}
                								
                						]
                				}
            				}
            		}
            ]
                       
        }
    }
}