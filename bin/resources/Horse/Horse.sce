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
            										"Pos": {"x": 0.0, "y": 0.0, "z": 150.0},
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
                		   							"ClearColor": { "r": 0.0, "g": 0.5, "b": 0.0, "a": 0.0 },
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
            										"Pos": {"x": 0.0, "y": 50.0, "z": 0.0},
                                "Forward": {"x": -1.0, "y": -1.0, "z": -1.0},
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
                				"Name": "Horse",
                				"SpaceOrder": 0,
                				"SpaceWorld": {
                                "Pos": {"x": 0.0, "y": 0.0, "z": 0.0},
                                "Forward": {"x": 0.0, "y": 0.0, "z": 1.0},
                                "Up": {"x": 0.0, "y": 1.0, "z": 0.0}
                        },
                				"Construct":{
                						"Class": "Essety",
                						"Name": "Horse",
                						"Component": [
                								{
                												"Class": "Render",
                                				"Name": "HorseRender",
                                				"Comesh": {
                                    				"Name": "HorseComesh", 
                                    				"NameFile": "./resources/Horse/horse.fwd",
                                    				"SpaceModel":{
                                    								 "Pos": {"x": 0.0, "y": 0.0, "z": 0.0},
                                    								 "Forward": {"x": 0.0, "y": -1.0, "z": 0.0},
                                    								 "Up": {"x": 0.0, "y": 0.0, "z": 1.0} 
                                    				},
                                    				"Meshes": [
                                        				{ "Name": "Horse",
                                          				"NameFile": "./resources/Horse/horse.fwd",
                                          				"Material": {
                                             				"Name": "HorseMaterial",
                                             				"NameFile": "./resources/Horse/Horse.mat"
                                             				},
                                          				"Skin": {
                                             				"Name": "Skin",
                                             				"NameFile": "./resources/Horse/horse.fwd",
                                             				"NameSkeleton": "Bip001"
                                             				}
                                        				},
                                        				{ "Name": "EyeBallLeft",
                                           				"NameFile": "./resources/Horse/horse.fwd",
                                           				"Material": {
                                                				"Name": "HorseEyeBallMaterial",
                                                				"NameFile": "./resources/Horse/HorseEyeBall.mat"
                                                				},
                                           				"Skin":{
                                              				"Name": "Skin",
                                              				"NameFile": "./resources/Horse/horse.fwd",
                                              				"NameSkeleton": "Bip001"
                                           				}
                                        				},
                                        				{ "Name": "EyeBallRight",
                                           				"NameFile": "./resources/Horse/horse.fwd",
                                           				"Material": {
                                                				"Name": "HorseEyeBallMaterial",
                                                				"NameFile": "./resources/Horse/HorseEyeBall.mat"
                                                				},
                                           				"Skin": {
                                              				"Name": "Skin",
                                              				"NameFile": "./resources/Horse/horse.fwd",
                                              				"NameSkeleton": "Bip001"
                                           				}
                                        				},
                                        				{   "Name": "ManeCard001",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard002",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard003",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard004",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard005",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard006",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard007",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "ManeCard008",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "ManeCardMaterial",
                                                				"NameFile": "./resources/Horse/ManeCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard001",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard002",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard003",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard004",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard005",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard006",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				},
                                        				{   "Name": "TailCard007",
                                            				"NameFile": "./resources/Horse/horse.fwd",
                                            				"Material": {
                                                				"Name": "TailCardMaterial",
                                                				"NameFile": "./resources/Horse/TailCard.mat"
                                                				},
                                            				"Skin": {
                                                				"Name": "Skin",
                                                				"NameFile": "./resources/Horse/horse.fwd",
                                                				"NameSkeleton": "Bip001"
                                            				}
                                        				}
                                    				]
                                				}
                								},
                								{
                										    "Class": "AnimationGroup",
                                				"Name": "HorseAniGroup",
                                				"NameFile": "./resources/Horse/horse.fwd",
                                				"Animation": {
                                    				"Name": "Take 001",
                                    				"NameFile": "./resources/Horse/horse.fwd",
                                    				"Skeleton": {
                                        				"Name": "Bip001",
                                        				"NameFile": "./resources/Horse/horse.fwd"
                                    				}
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