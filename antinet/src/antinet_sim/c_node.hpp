#ifndef C_NODE_HPP
#define C_NODE_HPP

#include "libs1.hpp"
#include "osi2.hpp"
#include "c_osi3_uuid_generator.hpp"
#include "c_world.hpp"
#include "c_msg.hpp"
#include "c_gui.hpp"

class c_osi2_switch;
class c_osi2_cable_direct; 
class c_osi2_nic;
class c_world;

// Classical switch in OSI layer 2
class c_osi2_switch : public c_entity {
	protected:
		static long int s_nr; ///< serial number of this object - the static counter
		long int m_nr; ///< serial number of this object
		
		c_world &m_world; ///< my netwok world in which I exist
		
		std::vector<c_osi2_nic> m_nic; ///< all my NIC cards, for all my ports
		
		const unsigned int m_connect_cost = 1;
	public:
		c_osi2_switch(c_world &world, const string &name, t_pos x, t_pos y);
		
		c_osi2_switch(const c_osi2_switch &) = delete; ///< copy constructor
		c_osi2_switch& operator = (const c_osi2_switch &)  = delete;
		c_osi2_switch(c_osi2_switch &&) = default; ///< move constructor
		c_osi2_switch& operator = (c_osi2_switch &&)  = default;
		
		void create_nic(); ///< adds one more NIC card
		c_osi2_nic & get_nic(unsigned int nr); ///< gets NIC with this number, throws if it does not exist
		c_osi2_nic & use_nic(unsigned int nr); ///< gets NIC with this number, can create it (and all other up to that number)
		size_t get_last_nic_index() const; ///< gets number of last NIC
		
		void connect_with(c_osi2_nic &target, c_world &world); ///< add port, connect to target, inside world
		
		unsigned int get_cost();
		
		void print(std::ostream &os) const;
		friend std::ostream& operator<<(std::ostream &os, const c_osi2_switch &obj);
		
		c_world & get_world() const;
		
		virtual void draw_allegro(c_drawtarget &drawtarget, c_layer &layer_any) override;
};

class c_node : public c_osi2_switch {
	private:	
		// TODO add s_nr m_nr print and operator<< like in others
		
	public:
		c_node(c_world &world, const string &name, t_pos x, t_pos y);
		c_node(const c_node &) = delete; ///< copy constructor
		c_node& operator = (const c_node &)  = delete;
		c_node(c_node &&) = default; ///< move constructor
		c_node& operator = (c_node &&)  = default;
		
		void send_packet(t_osi3_uuid remote_address, std::string &&data);
		virtual void draw_allegro(c_drawtarget &drawtarget, c_layer &layer_any) override;
};

#endif // C_NODE_HPP