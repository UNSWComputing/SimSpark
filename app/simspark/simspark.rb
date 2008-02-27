#
# simspark.rb
#

# toggle log file recording
$recordLogfile = false

sparkSetupServer()
sparkSetupRendering()
sparkSetupInput()

# sparkAddFPSCamera($scenePath+'camera', 
#                   -10,-10,5,15,248,4,false,2,10,10)

# let spark create a default camera
sparkAddFPSCamera(
 		  $scenePath+'camera', 
 		  x = -5, 
 		  y = -40, 
 		  z = 2,
                  vAngle = 10.0,
                  hAngle = 10.0,
                  maxSpeed = 15.0,
 		  accel = 400.0,
 		  drag = 4,
 		  addCollider = false,
                  colliderRadius = 2.0
 		  )

# setup default input bindings
run "bindings.rb"

# setup default materials common to all simulations
run "materials-default.rb"

#
# uncomment for logging setup (see spark.rb for reference)
#

sparkResetLogging()
sparkLogAllToCerr()
#sparkLogAllToFile('spark.txt')
#sparkLogDebugToCerr()

#
# uncomment any of the following to run a simulation
#

# create an arena with a bunch of boxes and spheres
# scene = get($scenePath)
# scene.importScene('rsg/boxspheres/simspark.rsg')

# create an arena to test various joint bodies
# scene = get($scenePath)
# scene.importScene('rsg/jointtest/simspark.rsg')

# source soccersim.rb to run the soccer simulation
run "soccersim.rb"

# setup game state info rendering for the internal monitor
# source soccersim.rb to run the soccer simulation
run "internalsoccermonitor.rb"
