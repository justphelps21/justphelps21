import csv
import sys


class Phone:
    def __init__(self, number, name):
        self.number = number
        self.name = name
        self.off = False
        self.being_called = False
        self.being_conference = False
        self.call_transfer_from = False
        self.call_transfer_to = False
        self.conference_transfer_from = False
        self.conference_transfer_to = False
        self.on_call = False
        self.on_conference = False
        self.call_list = []

    # take phone off hook if currently on hook, otherwise do nothing
    # if phone is currently being called, offhook will answer the call
    def off_hook(self, *phones):
        if not self.off and not self.being_called and not self.being_conference and not self.call_transfer_to \
                and not self.conference_transfer_to:
            self.off = True
            print(f'{self.number} hears dialtone')

        elif not self.off and self.being_called:
            self.off = True
            self.being_called = False
            if not self.on_call:
                self.on_call = True
                phones[0].on_call = True
                print(f'{phones[0].number} and {self.number} are talking')

        elif not self.off and self.being_conference:
            self.off = True
            self.being_conference = False

            if not self.on_conference:
                self.on_conference = True
                self.on_call = False
                phones[0].on_call = False
                phones[1].on_call = False
                phones[0].on_conference = True
                phones[1].on_conference = True
                print(f'{phones[0].number} and {phones[1].number} and {self.number} are talking')
        elif not self.off and self.call_transfer_to:
            self.off = True
            self.call_transfer_to = False
            self.on_call = True
            phones[0].on_call = False
            self.call_list.remove(phones[0])
            print(f'{phones[0].number} hears silence')
            print(f'{phones[1].number} and {self.number} are talking')
        elif not self.off and self.conference_transfer_to:
            self.off = True
            self.conference_transfer_to = False
            self.on_conference = True
            phones[0].on_conference = False
            self.call_list.remove(phones[0])
            print(f'{phones[0].number} hears silence')
            print(f'{phones[1].number} and {phones[2].number} and {self.number} are talking')
        else:
            pass

    def on_hook(self, *phones):
        if self.off and self.on_conference:
            self.off = False
            self.on_call = False
            self.on_conference = False
            phones[0].on_conference = False
            phones[1].on_conference = False
            phones[0].on_call = True
            phones[1].on_call = True
            phones[0].call_list.remove(self)
            phones[1].call_list.remove(self)
            print(f'{phones[0].number} and {phones[1].number} are talking')
            print(f'{self.number} hears silence')
            self.call_list.clear()
        elif self.off and self.on_call:
            self.off = False
            self.on_call = False
            phones[0].on_call = False
            print(f'{phones[0].number} hears silence')
            self.call_list.remove(phones[0])
            phones[0].call_list.remove(self)
        elif self.off:
            self.off = False
        else:
            pass

    def call(self, phone):
        if not self.off:
            print(f'{self.number} hears denial')
        elif self.off and not self.on_call and not phone.off:
            phone.being_called = True
            self.call_list.append(phone)
            phone.call_list.append(self)
            print(f'{self.number} hears ringback')
            print(f'{phone.number} hears ringing')
        elif self.off and not self.on_call and phone.off:
            print(f'{self.number} hears busy')
        else:
            print(f'{self.number} hears silence')

    def conference(self, *phones):
        if not self.off or self.off and len(self.call_list) != 1:
            print(f'{self.number} hears denial')
        if self.off and phones[0] in self.call_list and not phones[1].off:
            phones[1].being_conference = True
            self.call_list.append(phones[1])
            phones[0].call_list.append(phones[1])
            phones[1].call_list.append(self)
            phones[1].call_list.append(phones[0])
            print(f'{self.number} hears ringback')
            print(f'{phones[1].number} hears ringing')
        elif self.off and phones[1].off:
            print(f'{self.number} hears busy')
        else:
            print(f'{self.number} hears silence')


    def transfer(self, *phones):
        if not self.off:
            print(f'{self.number} hears silence')
        elif self.off and not self.on_call and not self.on_conference:
            print(f'{self.number} hears denial')
        elif self.off and self.on_call:
            if phones[1].off:
                print(f'{self.number} hears busy')
            else:
                self.call_transfer_from = True
                phones[1].call_transfer_to = True
                phones[1].call_list.append(self)
                phones[1].call_list.append(self.call_list[0])
                print(f'{self.number} hears ringback')
                print(f'{phones[1].number} hears ringing')
        elif self.off and self.on_conference:
            if phones[2].off:
                print(f'{self.number} hears busy')
            else:
                self.conference_transfer_from = True
                phones[2].conference_transfer_to = True
                phones[2].call_list.append(self)
                phones[2].call_list.append(self.call_list[0])
                phones[2].call_list.append(self.call_list[1])
                print(f'{self.number} hears ringback')
                print(f'{phones[2].number} hears ringing')

    def status(self):
        print(f'Number: {self.number}, Name: {self.name}')
        if not self.off:
            print(f'Phone is onhook')
        if self.off:
            print(f'Phone is offhook')
        if self.on_call:
            print(f'Phone is on a call with:\n'
                  f'{self.call_list[0].number}')
        if self.on_conference:
            print(f'Phone is on a conference call with:\n'
                  f'{self.call_list[0].number} and {self.call_list[1].number}')


def main():
    invalid_text = False
    phones = []
    phone_dict = {}
    with open('numbers.txt', 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if len(row[0]) != 5 or not row[0].isnumeric() or len(row[1]) < 1 or len(row[1]) >= 13 or not row[1].isalpha():
                print(f'Invalid input in file: numbers.txt\n'
                      f'Input must be in the format: "number,name" on each row, one per row\n'
                      f'number must be exactly 5 digits, name must be all alphabetical\n'
                      f'with length of at least 1 and no longer than 12')
                while True:
                    quit_app = input('Enter q to quit the application\n')

                    if quit_app == 'q':
                        sys.exit()
            phones.append(Phone(row[0], row[1]))
    if len(phones) > 20:
        del phones[20:]
    for phone in phones:
        phone_dict[phone.number] = phone.name
    if invalid_text:
        print(f'')
    print('Phones in system:')
    for key, value in phone_dict.items():
        print(key, ':', value)
    print('Valid commands:\n'
          'phone offhook (takes phone off hook)\n'
          'phone onhook (puts phone on hook)\n'
          'phone call phone (calls target phone)\n'
          'phone conference phone (conferences target phone)\n'
          'phone transfer phone (transfers to target phone)\n'
          'status (gives status of all phones in the system)\n'
          'q (quits the application)\n'
          '(use number or name in place of phone in each command)\n'
          'Phones in system are listed above')
    while True:
        command = input()
        split_command = command.split(' ')
        if command == 'q':
            break
        elif 'offhook' in command:
            for phone in phones:
                if split_command[0] == phone.number and phone.being_called is False and phone.being_conference is False \
                        and phone.call_transfer_to is False and phone.conference_transfer_to is False \
                        or split_command[0] == phone.name \
                        and phone.being_called is False and phone.being_conference is False and phone.call_transfer_to \
                        is False and phone.conference_transfer_to is False:
                    phone.off_hook()
                elif split_command[0] == phone.number and phone.being_conference is True or split_command[
                    0] == phone.name \
                        and phone.being_conference is True:
                    phone.off_hook(phone.call_list[0], phone.call_list[1])
                elif split_command[0] == phone.number and phone.being_called is True or split_command[0] == phone.name \
                        and phone.being_called is True:
                    phone.off_hook(phone.call_list[0])
                elif split_command[0] == phone.number and phone.call_transfer_to is True or split_command[0] == phone.name \
                        and phone.call_transfer_to is True:
                    phone.off_hook(phone.call_list[0], phone.call_list[1])
                elif split_command[0] == phone.number and phone.conference_transfer_to is True or split_command[0] == \
                        phone.name and phone.conference_transfer_to is True:
                    phone.off_hook(phone.call_list[0], phone.call_list[1], phone.call_list[2])
        elif 'onhook' in command:
            for phone in phones:
                if split_command[0] == phone.number and not phone.call_list or split_command[0] == phone.name \
                        and not phone.call_list:
                    phone.on_hook()
                elif split_command[0] == phone.number and len(phone.call_list) == 1 or split_command[0] == phone.name \
                        and len(phone.call_list) == 1:
                    phone.on_hook(phone.call_list[0])
                elif split_command[0] == phone.number and len(phone.call_list) == 2 or split_command[0] == phone.name \
                        and len(phone.call_list) == 2:
                    phone.on_hook(phone.call_list[0], phone.call_list[1])
        elif 'call' in command:
            valid_call_phone = False
            valid_receiving_phone = False
            for phone in phones:
                if split_command[0] == phone.number or split_command[0] == phone.name:
                    valid_call_phone = True
                    calling_phone = phone
            for phone in phones:
                if split_command[2] == phone.number or split_command[2] == phone.name:
                    valid_receiving_phone = True
                    receiving_phone = phone
            if valid_call_phone and valid_receiving_phone:
                calling_phone.call(receiving_phone)
        elif 'conference' in command:
            valid_conference_phone = False
            valid_conference_receive_phone = False
            for phone in phones:
                if split_command[0] == phone.number and len(phone.call_list) == 1 or split_command[0] == phone.name \
                        and len(phone.call_list) == 1:
                    valid_conference_phone = True
                    calling_phone = phone
            for phone in phones:
                if split_command[2] == phone.number or split_command[2] == phone.name:
                    valid_conference_receive_phone = True
                    receiving_phone = phone
            if valid_conference_phone and valid_conference_receive_phone:
                calling_phone.conference(calling_phone.call_list[0], receiving_phone)
        elif 'transfer' in command:
            valid_call_transfer_phone = False
            valid_conference_transfer_phone = False
            valid_transfer_receive_phone = False
            for phone in phones:
                if split_command[0] == phone.number and len(phone.call_list) == 1 or split_command[0] == phone.name \
                        and len(phone.call_list) == 1:
                    valid_call_transfer_phone = True
                    call_transferring_phone = phone
                elif split_command[0] == phone.number and len(phone.call_list) == 2 or split_command[0] == phone.name \
                        and len(phone.call_list) == 2:
                    valid_conference_transfer_phone = True
                    conference_transferring_phone = phone
            for phone in phones:
                if split_command[2] == phone.number or split_command[2] == phone.name:
                    valid_transfer_receive_phone = True
                    transferred_phone = phone
            if valid_call_transfer_phone and valid_transfer_receive_phone:
                call_transferring_phone.transfer(call_transferring_phone.call_list[0], transferred_phone)
            elif valid_conference_transfer_phone and valid_transfer_receive_phone:
                conference_transferring_phone.transfer(conference_transferring_phone.call_list[0],
                                                       conference_transferring_phone.call_list[1], transferred_phone)
        elif 'status' in command:
            for phone in phones:
                phone.status()


if __name__ == "__main__":
    main()
