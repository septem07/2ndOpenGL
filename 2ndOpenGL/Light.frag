#version 330 core
out vec4 FragColor;


void main()
{
   //FragColor = texture(ourTexture,coordsTexture);   //first from uniform(colour on texture) second from input by previous(coords)  
		//FragColor = mix(texture(ourTexture1,coordsTexture), texture(ourTexture2,coordsTexture), gamma); 
		FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}