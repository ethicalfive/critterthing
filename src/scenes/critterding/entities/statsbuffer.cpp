#include "statsbuffer.h"
#include "src/scenes/critterding/entities/critterb.h"
#include "src/scenes/critterding/entities/food.h"
#include "genotype.h"

using namespace std;

Statsbuffer* Statsbuffer::Instance () 
{
	static Statsbuffer t;
	return &t;
}

Statsbuffer::Statsbuffer()
 : recordInterval(100)
 , framecounter(0)
 , maxSnapshots(7680)
 , frameCounter(0)

{
// 	settings = Settings::Instance();

}

// void Statsbuffer::add( const vector<CritterB*>& critters, const vector<Food*>& food )
// void Statsbuffer::add( const vector<CritterB*>& critters, const vector<Entity*>& entities )
void Statsbuffer::add( const vector<CritterB*>& critters, const vector<Food*>& food )
{
	// get stats of this frame
	current.neurons	= 0;
	current.synapses	= 0;
	current.adamdistance	= 0;
	current.bodyparts	= 0;
	current.weight		= 0;
	if ( Settings::Instance()->getCVar("sams_mode") == 1 )
	{
		if (framecounter == 0 )
			current.fitnessindex	= 0;
	}
	else
		current.fitnessindex	= 0;
	
	CritterB* c;
	if (framecounter == 0 )
		current.fitnessindextotal = 0;

	current.critters = critters.size();
	
	
	
	
	for( unsigned int i=0; i < current.critters; ++i )
	{
		c = critters[i];
		current.neurons			+= c->brain.totalNeurons;
		current.synapses		+= c->brain.totalSynapses;
		current.adamdistance		+= c->genotype->adamdist;
		current.bodyparts		+= c->body.bodyparts.size() + c->body.mouths.size();
		current.weight			+= c->body.totalWeight;
		if ( framecounter <= Settings::Instance()->getCVar("critter_maxlifetime") + 1 )
		{
			//if ( c->fitness_index > 0)
			//	std::cerr << " framecounter: " << framecounter << " fitness_index: " << c->fitness_avg_height << ::endl;

			if ( framecounter  == Settings::Instance()->getCVar("critter_maxlifetime") - 2 )
			{
					current.fitnessindex += c->fitness_avg_height;
			//		std::cerr << "fitness_avg_height : " <<  c->fitness_avg_height << " fitness_index: " << current.fitnessindex << ::endl;
			}
		//	std::cerr << "fitness_avg_height : " <<  c->fitness_avg_height << " fitness_index: " << current.fitnessindex << ::endl;
			current.fitnessindextotal = c->fitness_best_height ;
		}
		
		
			
	}
	
	//std::cerr << "framecounter: " << framecounter << "avg height: " << current.fitnessindex << ::endl;
	//std::cerr << "framecounter: " << framecounter << "best height: " << current.fitnessindextotal << ::endl;
	//current.fitnessindex = current.fitnessindex / critters.size();
	
	
	
	//std::cerr << "fitnessindex" << current.fitnessindex << ::endl;
	
	//current.fitnessindex /= current.fitnessindex;
	

	// foodcount
		current.food			= food.size();
// 		unsigned int fcount(0);
// 		const auto& e_size(entities.size());
// 		for( unsigned int i(0); i < e_size; ++i)
// 		{
// 			Entity* e = entities[i];
// 			if ( e->type == FOOD )
// 			{
// 				++fcount;
// 			}
// 		}
// 		current.food			= fcount; // FIXME INTO FOODCOUNT loop

	if (Settings::Instance()->getCVar("sams_mode") == 1) 	
	{
		++framecounter;
		if ( framecounter  == Settings::Instance()->getCVar("critter_maxlifetime") - 1 )
		{
			current.fitnessindex = ( (current.fitnessindex / framecounter ) / Settings::Instance()->getCVar("mincritters") ) *100;
			current.fitnessindextotal = current.fitnessindextotal * 100;
		//	std::cerr << "mincritters: " << Settings::Instance()->getCVar("mincritters") << "critters.size: " << critters.size() << ::endl;
			std::cerr << " framecounter: " << framecounter << " avg height: " << current.fitnessindex / 100 << ::endl;
			std::cerr << " framecounter: " << framecounter << " best height: " << current.fitnessindextotal / 100 << ::endl;
			if ( snapshots.size() == maxSnapshots )
				snapshots.erase(snapshots.begin());

			// insert the current snapshot
			snapshots.push_back(current);

			findHighestGraphValue();

		}
		if ( framecounter  == Settings::Instance()->getCVar("critter_maxlifetime") )
			framecounter = 0;
		
	}
	else 
		if ( ++framecounter == recordInterval )
		{
			// remove expired snapshots
			if ( snapshots.size() == maxSnapshots )
				snapshots.erase(snapshots.begin());

			// insert the current snapshot
			snapshots.push_back(current);

			findHighestGraphValue();

			framecounter = 0;
		}
}

void Statsbuffer::findHighestGraphValue()
{
// find the highest value in the stats vector
	m_graph_highest = 0;
	for ( unsigned int i=m_graph_consider_highest_start; i < snapshots.size(); ++i )
	{
		auto const& sn( snapshots[i] );
		if ( Settings::Instance()->getCVar("sams_mode") == 0 )
		{
		if ( sn.food > m_graph_highest )
			m_graph_highest = sn.food;

		if ( sn.critters > m_graph_highest )
			m_graph_highest = sn.critters;
		}
		
		if (Settings::Instance()->getCVar("sams_mode") == 1)
		{
		//	std::cerr << " graph - framecounter: " << framecounter << " avg height: " << sn.fitnessindex << ::endl;
		//	std::cerr << " graph - framecounter: " << framecounter << " best height: " << sn.fitnessindextotal << ::endl;
			if ( sn.fitnessindextotal > sn.fitnessindex )
			{
				if ( m_graph_highest < sn.fitnessindextotal)
					m_graph_highest = sn.fitnessindextotal;
				
			}
			else
			{
				if ( m_graph_highest < sn.fitnessindex)
					m_graph_highest = sn.fitnessindex;
			}
		//	std::cerr << " m_graph_highest: " << m_graph_highest << ::endl;
			

			
		}
	}
}