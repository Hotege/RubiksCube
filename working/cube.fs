
varying vec4 positionOutput;
varying vec4 colorOutput;
varying vec4 centerOutput;

void main()
{
	float dx = distance(positionOutput.x, centerOutput.x);
	float dy = distance(positionOutput.y, centerOutput.y);
	float dz = distance(positionOutput.z, centerOutput.z);
	if (dx > 0.45 || dy > 0.45 || dz > 0.45)
		gl_FragColor = vec4(0.25, 0.25, 0.25, 1.0);
	else
		gl_FragColor = colorOutput;
}