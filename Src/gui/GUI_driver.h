#ifndef GUI_DRIVER_H_
#define GUI_DRIVER_H_

class GUI_Driver {

	public:
		virtual ~GUI_Driver() {}

		virtual bool isPausa() = 0;
		virtual bool isFim() = 0;
		virtual void setFim( bool fim ) = 0;

};

#endif
