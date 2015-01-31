local io = require("io")
local http = require("socket.http")

scriptId = 'com.thalmic.examples.myofan'
scriptTitle = "Myo Fan"
scriptDetailsUrl = "" -- not important

SPEED_CONTINUOUS_TIMEOUT = 1000
SPEED_LAST = 0

IP_ADDRESS = '192.168.42.5'

function activeAppName()
    return "Myo Fan"
end

function onForegroundWindowChange(app, title)
    -- TODO: make the foreground be the arduino serial output
    return true
end

-- Periodically go through to check if fan speed needs to be increased.
function onPeriodic()
	if (myo.isUnlocked()) then
		local now = myo.getTimeMilliseconds()
		if (now > (SPEED_CONTINUOUS_TIMEOUT + SPEED_LAST) ) then
			local currentPitch = myo.getPitch()
			if (currentPitch > 0.5) then
				speed_up()
				SPEED_LAST = myo.getTimeMilliseconds()
			elseif (currentPitch < -0.5) then
				speed_down()
				SPEED_LAST = myo.getTimeMilliseconds()
			end
		end
	end
end

-- Includes keyboard commands for moving the fan
function rotate()
	http.request{
		url = "http://" .. IP_ADDRESS .. "/action=rotate",
	}
end

function stop_rotate()
	http.request{
		url = "http://" .. IP_ADDRESS .. "/action=norotate",
	}
end

function speed_up()
	http.request{
		url = "http://" .. IP_ADDRESS .. "/action=speedup",
	}
end

function speed_down()
	http.request{
		url = "http://" .. IP_ADDRESS .. "/action=speeddown",
	}
end


-- Used to fix waves dependent on left/right hand use
function conditionallySwapWave(pose)
	if myo.getArm() == left then
		if pose == "waveIn" then
			pose = "waveOut"
		elseif pose == "waveOut" then
			pose = "waveIn"
		end
	end
	return pose
end

-- Most commands aside from speed are mapped to poses.
function onPoseEdge(pose, edge)
	-- Swap wave poses based on lef/right hand by calling function.
	if pose == "waveIn" or pose == "waveOut" then
		if edge == "on" then
			pose = conditionallySwapWave(pose)
		end
	end

	if edge == "on" then
		if pose == "waveIn" then
    		rotate()
		elseif pose == "waveOut" then
			stop_rotate()
		-- spread fingers and fist used for unlocking/locking
		elseif pose == "fingersSpread" then
			myo.unlock("hold")
			myo.notifyUserAction()
		elseif pose == "fist" then
			myo.lock()
			myo.notifyUserAction()
		end
	end
end

function onActiveChange(isActive)
end
