#ifndef SAMSMODE_H
#define SAMSMODE_H

#include "../entities/worldb.h"

class SamsMode : public WorldB {

	public:
		SamsMode(  boost::shared_ptr<BeGraphicsSystem> system, BeFilesystem& fileSystem, boost::shared_ptr<Textverbosemessage> textverbosemessage );
		~SamsMode();

		void		process(const BeTimer& timer);
		void		init();
		void		insertCritter();
		void		loadAllCritters();
	private:
		void		makeFloor();
		void		insRandomCritter(int nr);
		void		insMutatedCritter(CritterB& other, int nr, unsigned int id, bool mutateBrain, bool mutateBody);
		void		insFood(int nr);
		
		float		critterspacing;

		bool		haveWinner;

		unsigned int	framecounter;
		unsigned int	m_finished_counter;
		
		unsigned int	testcounter;
		boost::shared_ptr<BeGraphicsModelResource>	m_model_cube;
		virtual void resetCamera();
// 		virtual void setLights();
};

#endif
