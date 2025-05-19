 #for spotify api

import requests
import base64 #libs for encoding and extraction

client_id = 'REDACTED' #client id / apikey
client_secret = 'REDACTED'

base64_auth = base64.b64encode(f'{client_id}:{client_secret}'.encode()).decode()

def token():
    auth_url = 'https://accounts.spotify.com/api/token' #auth call
    auth_data = {
        'grant_type': 'client_credentials', 
    }
    headers = {
        'Authorization': f'Basic {base64_auth}', #auth
    }

    response = requests.post(auth_url, data=auth_data, headers=headers)
    if response.status_code == 200:
        access_token = response.json().get('access_token') #trap
        return access_token
    else:
        print(f'Error getting access token: {response.status_code}')
        return None

def extplay(playlist_url):
    parts = playlist_url.split('/') #extract
    playlist_id = parts[-1]
    return playlist_id

def fetch_playlist_data(playlist_id, access_token): #get playlist data
    api_url = f'https://api.spotify.com/v1/playlists/{playlist_id}'
    headers = {
        'Authorization': f'Bearer {access_token}',
    }

    response = requests.get(api_url, headers=headers)

    if response.status_code == 200: #traps
        return response.json()
    else:
        print(f'Error fetching playlist data: {response.status_code}')
        return None

def writetofile(songs, file_path): #writing to txt file
    with open(file_path, 'w') as file:
        for song in songs:
            file.write(song + '\n')

def main():
    playlist_url = str(input('Paste the spotify playlist URL: ')) #gets custom playlist
    access_token = token()
    if access_token: #calls
        playlist_id = extplay(playlist_url)
        playlist_data = fetch_playlist_data(playlist_id, access_token)
        if playlist_data:
            songs = [track['track']['name'] for track in playlist_data['tracks']['items']]
            writetofile(songs, 'track_list.txt') #write

if __name__ == "__main__":
    main() #direct to main
