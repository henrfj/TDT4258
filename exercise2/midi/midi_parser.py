import sys
from os import path
import mido

A = 1.059463094359
F_0 = 440
NOTE_0 = 69 # A4 where C4 is 60
NOTE_NAMES = ("C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B")

CPU_FREQ = 14000000

get_freq = lambda note: round(F_0 * pow(A, note - NOTE_0), 3)
get_speed = lambda time: round(time // 250) + 1

if len(sys.argv) < 2:
    print("Usage {} filename.mid".format(sys.argv[0]))
    sys.exit(1)

with open('songs.h', 'w') as ofile:
    ofile.write('#ifndef _SONGS_H\n#define _SONGS_H\n\n')
    ofile.write('#define SONG(id) (\\\n')
    for ind, file_name in enumerate(sys.argv[1:]):
        ofile.write('\t\tid=={} ? song{} : \\\n'.format(str(ind), str(ind)))
    ofile.write('\t\tsong0) //default\n')
    ofile.write('#define SONG_AMPL(id) (\\\n')
    for ind, file_name in enumerate(sys.argv[1:]):
        ofile.write('\t\tid=={} ? song{}_ampl : \\\n'.format(str(ind), str(ind)))
    ofile.write('\t\tsong0_ampl) //default\n')
    ofile.write('#define SONG_SPD(id) (\\\n')
    for ind, file_name in enumerate(sys.argv[1:]):
        ofile.write('\t\tid=={} ? song{}_spd : \\\n'.format(str(ind), str(ind)))
    ofile.write('\t\tsong0_spd) //default\n')
    for ind, file_name in enumerate(sys.argv[1:]):
        if not file_name.endswith('.mid'):
            print("Mid file not provided, please pass a file with extension `mid`")
            sys.exit(2)
        mid = mido.MidiFile(file_name)
        notes = []
        velocities = []
        times = []
        print(file_name)
        for track in mid.tracks:
            for msg in track:
                if msg.type == 'note_on' and msg.channel == 0:
                    note = msg.note
                    freq = get_freq(note)
                    octave = (note//12) - 1
                    name = NOTE_NAMES[note % 12]
                    divider = int(CPU_FREQ // (2*freq)) #double frequency to get both edges
                    print("{} ({} {}) at {} Hz ({})".format(note, name, octave, freq, divider))
                    #print(msg)
                    #convert later the frequency
                    notes.append(freq)
                    velocities.append(msg.velocity)
                    times.append(get_speed(msg.time))
                #if msg.type == 'note_off':
                #    print(msg)

        if velocities:
            max_v = max(velocities)
            min_v = min(velocities)
            if max_v != min_v:
                for i, v in enumerate(velocities):
                    velocities[i] = 14 * (v-min_v) // (max_v - min_v) + 1
            else:
                velocities = [5 for v in velocities]

        def write_array(ofile, data_type, arr_name, arr, cols):
            ofile.write('const {} {}[{}] = {{\n\t'
                        .format(data_type, arr_name, len(arr)))
            for i, n in enumerate(arr):
                if i % cols == cols-1:
                    ofile.write('{},\n\t'.format(n))
                elif i == len(arr)-1:
                    ofile.write('{}'.format(n))
                else:
                    ofile.write('{}, '.format(n))
            ofile.write('\n};\n')

        name = 'song' + str(ind)
        ofile.write('\n//{}\n'.format(path.splitext(path.basename(file_name))[0]))
        notes.insert(0, len(notes))
        write_array(ofile, 'float', name, notes, 7)
        velocities.insert(0, 0) #length not used here (and may not fit), same as notes
        write_array(ofile, 'uint8_t', name+'_ampl', velocities, 15)
        times.insert(0, 0) #length not used here (and may not fit), same as notes
        write_array(ofile, 'uint8_t', name+'_spd', times, 15)
    ofile.write('\n#endif\n')
