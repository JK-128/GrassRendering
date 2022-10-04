//This shader uses noise functions provided through:
// https://github.com/ashima/webgl-noise
//MIT license file provided in the repo.

#version 460
layout (location = 0) in vec3  position;
layout (location = 1) in vec3  offset;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

uniform float time;
uniform float noiseX;
uniform float noiseZ;
uniform float noiseS;
uniform float noiseC;
uniform float wScale;
uniform float strength;
uniform float grassHeight;
uniform float brightness;
uniform float contrast;
uniform float windSpeed;

vec4 mod289(vec4 x)
{
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x)
{
  return mod289(((x*34.0)+10.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t) {
  return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec2 P)
{
  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
  Pi = mod289(Pi); // To avoid truncation effects in permutation
  vec4 ix = Pi.xzxz;
  vec4 iy = Pi.yyww;
  vec4 fx = Pf.xzxz;
  vec4 fy = Pf.yyww;

  vec4 i = permute(permute(ix) + iy);

  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
  vec4 gy = abs(gx) - 0.5 ;
  vec4 tx = floor(gx + 0.5);
  gx = gx - tx;

  vec2 g00 = vec2(gx.x,gy.x);
  vec2 g10 = vec2(gx.y,gy.y);
  vec2 g01 = vec2(gx.z,gy.z);
  vec2 g11 = vec2(gx.w,gy.w);

  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
  g00 *= norm.x;  
  g01 *= norm.y;  
  g10 *= norm.z;  
  g11 *= norm.w;  

  float n00 = dot(g00, vec2(fx.x, fy.x));
  float n10 = dot(g10, vec2(fx.y, fy.y));
  float n01 = dot(g01, vec2(fx.z, fy.z));
  float n11 = dot(g11, vec2(fx.w, fy.w));

  vec2 fade_xy = fade(Pf.xy);
  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
  return 2.3 * n_xy;
}

vec2 random2(vec2 p)
{
	return fract(sin(vec2(
	dot(p, vec2(127.32, 231.4)),
	dot(p, vec2(12.3, 146.3))))* 231.23);
}

float worleyNoise(vec2 p)
{
	float dist = 1.0;

	vec2 i_p = floor(p);
	vec2 f_p = fract(p);

	for(int y = -1; y <= 1; y++)
	{
		for(int x = -1; x <= 1; x++)
		{
			vec2 n = vec2(float(x), float(y));
			vec2 d = n + random2(i_p + n) - f_p;

			dist = min(dist, length(d));
		}
	}

	return dist;
}

out float height;

//Testing out adding interactivity.
uniform vec3  interTarget = vec3(0.0);
uniform float interStrength = 0.5;
uniform float interRadius = 1.0;
uniform float interBRadius = 1.0;

void main()
{
	vec3 groundOffset = vec3(offset.x, 0.0, offset.z);
	vec2 noiseVec     = vec2(groundOffset.x * noiseX, groundOffset.z * noiseZ);

	float noiseVal = cnoise(noiseVec);

	groundOffset.y += position.y * (offset.y * grassHeight + (noiseVal * noiseS));

	height = noiseVal + brightness + (groundOffset.y * contrast);
	height = ((1.0 - height) * noiseC) + height;

	vec2 worleyVec = vec2(groundOffset.x, groundOffset.z) + (time * vec2(windSpeed, 0.0));

	float wNoise = worleyNoise(worleyVec * wScale);

	//vec3 realPos = vec3(position.x, position.y, position.z);

	//Interactivity stuff.
	mat4 worldMat = model;

	vec3 worldSpace = (worldMat * vec4(groundOffset, 1.0)).xyz;
	vec3 direction = worldSpace - interTarget;
	
	direction.y = 0.0;
	direction = normalize(direction);

	float dist  = distance(interTarget, worldSpace);
	float power = smoothstep(interRadius, 0.0, dist);
	
	direction = (vec4(direction, 1.0) * worldMat).xyz;
	direction = normalize(direction);

	vec3 realPos = position + (direction * power * interStrength * (interBRadius + position.y));

	groundOffset.x += position.y * wNoise * strength;
	groundOffset.z += position.y * wNoise * strength;
	

	gl_Position = projection * view * model * vec4(realPos + groundOffset, 1.0);
}