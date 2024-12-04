import websockets
import asyncio
import cv2
import numpy as np

async def connect_camera(url):
    async with websockets.connect(url) as ws:
        while True:
            img_binary_data = await ws.recv()
            encoded_img = np.frombuffer(img_binary_data, dtype = np.uint8)
            img = cv2.imdecode(encoded_img, cv2.IMREAD_COLOR)
            cv2.imshow("esp32cam", img)
            if cv2.waitKey(1) & 0xFF0 == ord('q'):
                break
        cv2.destroyAllWindows()

async def connect_control(url):
    async with websockets.connect(url) as ws:
        while True:
            user_msg = await asyncio.to_thread(input, "Enter your message: ")
            await ws.send(user_msg) 
            print(f"Sent: {user_msg}")

async def main():
    print('Start')
    #control_url = "ws://cobot.center:8286/pang/ws/sub?channel=bq5ame6g10l3jia3h0ng&track=colink&mode=bundle"
    #camera_url = "ws://cobot.center:8286/pang/ws/sub?channel=bq5ame6g10l3jia3h0ng&track=video"
    control_url = "ws://cobot.center:8286/pang/ws/sub?channel=cmmvr9epjh64ovedk470&track=colink&mode=bundle"
    camera_url = "ws://cobot.center:8286/pang/ws/sub?channel=cmmvr9epjh64ovedk470&track=video"
    
    control = asyncio.create_task(connect_control(control_url))
    camera = asyncio.create_task(connect_camera(camera_url))

    await asyncio.gather(control, camera)

if __name__ == "__main__":
    asyncio.run(main())
