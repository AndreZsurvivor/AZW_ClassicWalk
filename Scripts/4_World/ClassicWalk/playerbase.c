modded class PlayerBase
{
	const float JOG_TILT  = 30;		// tilt zone limits in degrees
	const float WALK_TILT = 43;		//
	const float WEIGHT_INFLUENCE_FACTOR = 3; // set 0 - 5
	const float HEAVY_LOAD = 5000;	// player load weight limit in g for sprinting downhill
	
	private float m_AdjustedJogTilt = JOG_TILT;			// tilt zone limits after weight adjustment
	private float m_AdjustedWalkTilt = WALK_TILT;		//	
	private float m_LastElevation = 0;	// logs elevation

	
	override bool CanSprint()
	{
		super.CanSprint();
		
		vector pos_player 		= GetPosition();
		float elevationTrend 	= pos_player[1] - m_LastElevation;
		m_LastElevation 		= pos_player[1];
		bool playerGrounded 	= IsPlayerGrounded(pos_player);
		float tilt 				= GetSurfaceTilt(pos_player);
		
		float playerLoad 		= GetPlayerLoad();				
		AdjustTiltLimits(playerLoad);
		float jogTilt 			= GetAdjustedJogTiltLimit();
		float walkTilt 			= GetAdjustedWalkTiltLimit();
		
		// Player with heavy load can't sprint downhill
		if ((tilt > jogTilt) && (tilt != 0) && (playerLoad > HEAVY_LOAD) && playerGrounded && (elevationTrend < 0.0))
		{
			GetUApi().GetInputByName("UAWalkRunTemp").ForceEnable(false);
			//Print("HEAVY DOWNHILL_FORCE JOG");
			return false;
		}
				
		// Player is going uphill and can't sprint
		if ((tilt <= walkTilt) && (tilt > jogTilt) && (tilt != 0) && playerGrounded && (elevationTrend > 0.01))
		{
			GetUApi().GetInputByName("UAWalkRunTemp").ForceEnable(false);
			//Print("FORCE JOG");
			return false;
		}
						
		// Player is going steep uphill and can only walk
		if ((tilt > walkTilt) && (tilt != 0) && playerGrounded && (elevationTrend > 0.02))
		{			
			GetUApi().GetInputByName("UAWalkRunTemp").ForceEnable(true);
			//Print("FORCE WALK");
			return false;
		} 
		
		// DISABLE ANY RESTRICTIONS
		//Print("FREE");
		GetUApi().GetInputByName("UAWalkRunTemp").ForceEnable(false);			
		return true;	
	}
	
	float GetAdjustedJogTiltLimit()
	{
		return m_AdjustedJogTilt;
	}
	
	float GetAdjustedWalkTiltLimit()
	{
		return m_AdjustedWalkTilt;
	}
	
	float GetSurfaceTilt(vector position)
	{
		vector tiltVec = GetGame().GetSurfaceOrientation( position[0],  position[2]);
		float tilt = 360 - tiltVec[1];
		return tilt;
	}
		
	float GetPlayerLoad()
	{
		float playerLoad = GetGame().GetPlayer().GetWeightEx();
		return playerLoad;
	}
	
	bool IsPlayerGrounded(vector playerPos)
	{	
		float playerIsGrounded;	
		float height = GetGame().SurfaceY(playerPos[0], playerPos[2]);
		height = playerPos[1] - height;
									
		if (height > 0.4)
		{
			playerIsGrounded = false;
		}
		else
		{
			playerIsGrounded = true;
		}
		return playerIsGrounded;
	}
	
	private void AdjustTiltLimits(float playerLoad)
	{
		m_AdjustedJogTilt = JOG_TILT - (playerLoad * WEIGHT_INFLUENCE_FACTOR / 6000);
		m_AdjustedWalkTilt = WALK_TILT - (playerLoad * WEIGHT_INFLUENCE_FACTOR / 10000);
	}	
}