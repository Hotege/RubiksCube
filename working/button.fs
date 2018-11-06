
varying vec2 texcoordOutput;
uniform sampler2D texInput;
uniform vec4 colorBack;
uniform vec4 colorText;

void main()
{
	vec4 colorTex = texture2D(texInput, texcoordOutput);
	gl_FragColor = vec4(
		colorBack.x * (1.0 - colorTex.x) + colorText.x * colorTex.x,
		colorBack.y * (1.0 - colorTex.y) + colorText.y * colorTex.y,
		colorBack.z * (1.0 - colorTex.z) + colorText.z * colorTex.z,
		colorBack.w * (1.0 - colorTex.w) + colorText.w * colorTex.w
	);
}