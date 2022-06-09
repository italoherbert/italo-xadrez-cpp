
#ifndef AUDIO_IMAGEM_H
#define AUDIO_IMAGEM_H

class AudioImagem {
	
	private:
		int x;
		int y;
		int w;
		int h;
		
	public:
		AudioImagem( TelaDriver* drv );
		
		int getX();
		int getY();
		int getLargura();
		int getAltura();
	
};

#endif
