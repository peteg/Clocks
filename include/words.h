/*
 * Words as SP0256 allophones.
 *
 * Lifted from various sources:
 *  - the Radio Shack SP0256 data sheet
 *  - the Talking Electronics #15 "Speech Module" article
 *  - ...
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef _WORDS_H_
#define _WORDS_H_

#include <stdint.h>
#include <time.h>

#include "allophones.h"

/* Driver provided elsewhere */
struct sp0256;
void sp0256_allophone(const struct sp0256 *, const allophone_t);

/* Derived functions provided here */
void sp0256_allophones(const struct sp0256 *, const allophone_t[]);
void sp0256_phrase(const struct sp0256 *, const allophone_t * const[]);
void sp0256_sentence(const struct sp0256 *, ...);

void sp0256_number(struct sp0256 *, int16_t);

void sp0256_pressure(struct sp0256 *, int pressure); // FIXME not small-device friendly
void sp0256_temp(struct sp0256 *, uint16_t);
void sp0256_time(struct sp0256 *, const struct tm);

/* Words */

extern const allophone_t a_PA1[];
extern const allophone_t a_PA2[];
extern const allophone_t a_PA3[];
extern const allophone_t a_PA4[];
extern const allophone_t a_PA5[];

extern const allophone_t * const a_decades[];
extern const allophone_t * const a_numbers[];
extern const allophone_t a_hundred[];
extern const allophone_t a_hundreds[];
extern const allophone_t a_thousand[];
extern const allophone_t a_million[];

extern const allophone_t a_AM[];
extern const allophone_t a_Hertz[];
extern const allophone_t a_PM[];
extern const allophone_t a_alarm[];
extern const allophone_t a_all[];
extern const allophone_t a_am[];
extern const allophone_t a_amateur[];
extern const allophone_t a_an[];
extern const allophone_t a_and[] ;
extern const allophone_t a_are[];
extern const allophone_t a_at[];
extern const allophone_t a_baby[];
extern const allophone_t a_bathe[];
extern const allophone_t a_bather[];
extern const allophone_t a_bathing[];
extern const allophone_t a_be[];
extern const allophone_t a_beer[];
extern const allophone_t a_birthday[];
extern const allophone_t a_bite[];
extern const allophone_t a_blank[];
extern const allophone_t a_bread[];
extern const allophone_t a_brother[];
extern const allophone_t a_by[];
extern const allophone_t a_byte[];
extern const allophone_t a_bytes[];
extern const allophone_t a_calendar[];
extern const allophone_t a_calling[];
extern const allophone_t a_cat[];
extern const allophone_t a_check[];
extern const allophone_t a_checked[];
extern const allophone_t a_checker[];
extern const allophone_t a_checkers[];
extern const allophone_t a_checking[];
extern const allophone_t a_checks[];
extern const allophone_t a_clock[];
extern const allophone_t a_close[];
extern const allophone_t a_clown[];
extern const allophone_t a_cognitive[];
extern const allophone_t a_collide[];
extern const allophone_t a_computer[];
extern const allophone_t a_cookie[];
extern const allophone_t a_coop[];
extern const allophone_t a_correct[];
extern const allophone_t a_corrected[];
extern const allophone_t a_correcting[];
extern const allophone_t a_corrects[];
extern const allophone_t a_crane[];
extern const allophone_t a_crown[];
extern const allophone_t a_data[];
extern const allophone_t a_date[];
extern const allophone_t a_daughter[];
extern const allophone_t a_day[];
extern const allophone_t a_degrees[];
extern const allophone_t a_disk[];
extern const allophone_t a_divided[];
extern const allophone_t a_do[];
extern const allophone_t a_down[];
extern const allophone_t a_drive[];
extern const allophone_t a_drives[];
extern const allophone_t a_east[];
extern const allophone_t a_emergency[];
extern const allophone_t a_emotional[];
extern const allophone_t a_engage[];
extern const allophone_t a_engagement[];
extern const allophone_t a_engages[];
extern const allophone_t a_engaging[];
extern const allophone_t a_enrage[];
extern const allophone_t a_enraged[];
extern const allophone_t a_enrages[];
extern const allophone_t a_enraging[];
extern const allophone_t a_equal[];
extern const allophone_t a_equals[];
extern const allophone_t a_error[];
extern const allophone_t a_escape[];
extern const allophone_t a_escaped[];
extern const allophone_t a_escapes[];
extern const allophone_t a_escaping[];
extern const allophone_t a_extent[];
extern const allophone_t a_exterminate[];
extern const allophone_t a_father[];
extern const allophone_t a_fir[];
extern const allophone_t a_fool[];
extern const allophone_t a_force[];
extern const allophone_t a_freeze[];
extern const allophone_t a_freezers[];
extern const allophone_t a_from[];
extern const allophone_t a_frozen[];
extern const allophone_t a_gauge[];
extern const allophone_t a_gauged[];
extern const allophone_t a_gauger[];
extern const allophone_t a_gauging[];
extern const allophone_t a_happy[];
extern const allophone_t a_has[];
extern const allophone_t a_have[];
extern const allophone_t a_hello[];
extern const allophone_t a_hour[];
extern const allophone_t a_hours[];
extern const allophone_t a_how[];
extern const allophone_t a_idiot[];
extern const allophone_t a_in[];
extern const allophone_t a_infinitive[];
extern const allophone_t a_input[];
extern const allophone_t a_intrigue[];
extern const allophone_t a_intrigued[];
extern const allophone_t a_intrigues[];
extern const allophone_t a_intriguing[];
extern const allophone_t a_investigate[];
extern const allophone_t a_investigated[];
extern const allophone_t a_investigates[];
extern const allophone_t a_investigating[];
extern const allophone_t a_investigator[];
extern const allophone_t a_investigators[];
extern const allophone_t a_is[];
extern const allophone_t a_it[];
extern const allophone_t a_key[];
extern const allophone_t a_left[];
extern const allophone_t a_legislate[];
extern const allophone_t a_legislated[];
extern const allophone_t a_legislates[];
extern const allophone_t a_legislating[];
extern const allophone_t a_legislature[];
extern const allophone_t a_letter[];
extern const allophone_t a_litter[];
extern const allophone_t a_little[];
extern const allophone_t a_live[];
extern const allophone_t a_memories[];
extern const allophone_t a_memory[];
extern const allophone_t a_minus[];
extern const allophone_t a_minute[];
extern const allophone_t a_minutes[];
extern const allophone_t a_modem[];
extern const allophone_t a_month[];
extern const allophone_t a_mother[];
extern const allophone_t a_my[];
extern const allophone_t a_name[];
extern const allophone_t a_naughty[];
extern const allophone_t a_nip[];
extern const allophone_t a_nipped[];
extern const allophone_t a_nipping[];
extern const allophone_t a_nips[];
extern const allophone_t a_no[];
extern const allophone_t a_of[];
extern const allophone_t a_on[];
extern const allophone_t a_or[];
extern const allophone_t a_our[];
extern const allophone_t a_past[];
extern const allophone_t a_physical[];
extern const allophone_t a_pin[];
extern const allophone_t a_pinned[];
extern const allophone_t a_pinning[];
extern const allophone_t a_pins[];
extern const allophone_t a_pledge[];
extern const allophone_t a_pledges[];
extern const allophone_t a_pledging[];
extern const allophone_t a_plus[];
extern const allophone_t a_point[];
extern const allophone_t a_pressure[];
extern const allophone_t a_ram[];
extern const allophone_t a_ray[];
extern const allophone_t a_rays[];
extern const allophone_t a_ready[];
extern const allophone_t a_red[];
extern const allophone_t a_right[];
extern const allophone_t a_robot[];
extern const allophone_t a_robots[];
extern const allophone_t a_score[];
extern const allophone_t a_second[];
extern const allophone_t a_seconds[];
extern const allophone_t a_sensitive[];
extern const allophone_t a_sensitivity[];
extern const allophone_t a_sensors[];
extern const allophone_t a_sincere[];
extern const allophone_t a_sincerely[];
extern const allophone_t a_sincerity[];
extern const allophone_t a_sister[];
extern const allophone_t a_son[];
extern const allophone_t a_sound[];
extern const allophone_t a_south[];
extern const allophone_t a_space[];
extern const allophone_t a_speak[];
extern const allophone_t a_speech[];
extern const allophone_t a_spell[];
extern const allophone_t a_spelled[];
extern const allophone_t a_speller[];
extern const allophone_t a_spellers[];
extern const allophone_t a_spelling[];
extern const allophone_t a_spells[];
extern const allophone_t a_start[];
extern const allophone_t a_started[];
extern const allophone_t a_starter[];
extern const allophone_t a_starting[];
extern const allophone_t a_starts[];
extern const allophone_t a_statement[];
extern const allophone_t a_stop[];
extern const allophone_t a_stopped[];
extern const allophone_t a_stopper[];
extern const allophone_t a_stopping[];
extern const allophone_t a_stops[];
extern const allophone_t a_subject_noun[];
extern const allophone_t a_subject_verb[];
extern const allophone_t a_sweat[];
extern const allophone_t a_sweated[];
extern const allophone_t a_sweater[];
extern const allophone_t a_sweaters[];
extern const allophone_t a_sweating[];
extern const allophone_t a_switch[];
extern const allophone_t a_switched[];
extern const allophone_t a_switches[];
extern const allophone_t a_switching[];
extern const allophone_t a_system[];
extern const allophone_t a_systems[];
extern const allophone_t a_talk[];
extern const allophone_t a_talked[];
extern const allophone_t a_talker[];
extern const allophone_t a_talkers[];
extern const allophone_t a_talking[];
extern const allophone_t a_talks[];
extern const allophone_t a_television[];
extern const allophone_t a_temperature[];
extern const allophone_t a_test[];
extern const allophone_t a_the[];
extern const allophone_t a_then[];
extern const allophone_t a_there[];
extern const allophone_t a_this[];
extern const allophone_t a_thread[];
extern const allophone_t a_threaded[];
extern const allophone_t a_threader[];
extern const allophone_t a_threaders[];
extern const allophone_t a_threading[];
extern const allophone_t a_threads[];
extern const allophone_t a_time[];
extern const allophone_t a_times[];
extern const allophone_t a_to[];
extern const allophone_t a_today[];
extern const allophone_t a_uncle[];
extern const allophone_t a_up[];
extern const allophone_t a_vision[];
extern const allophone_t a_want[];
extern const allophone_t a_whale[];
extern const allophone_t a_whaler[];
extern const allophone_t a_whalers[];
extern const allophone_t a_whales[];
extern const allophone_t a_whaling[];
extern const allophone_t a_what[];
extern const allophone_t a_who[];
extern const allophone_t a_with[];
extern const allophone_t a_year[];
extern const allophone_t a_yes[];
extern const allophone_t a_you[];
extern const allophone_t a_your[];

extern const allophone_t * a_fur;
extern const allophone_t * a_know;

extern const allophone_t a_mega[];
extern const allophone_t a_kilo[];
extern const allophone_t a_hecto[];

extern const allophone_t a_pascals[];

extern const allophone_t * const a_days[];
extern const allophone_t * const a_months[];

extern const allophone_t * const a_chars[];
#define a_chars_len 26

#endif /* _WORDS_H_ */
