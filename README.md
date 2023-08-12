##ros2_opencv_base
This is a ros2 repo for working with openCV it has two launch files.
```bash
$ ros2 launch opencv_package camera.launch.py
```
will launch a publisher that publishes 'video0' from your computer. If you're using a laptop this will probably be the webcam. You don't have to use this launch if you already have an image topic to work with.

```bash
$ ros2 launch opencv_package opencv_package.launch.py
```

Will launch the node itself the node by itself is useless it just takes a ros image msg and creates a OpenCV Mat object with it and then converts it back to ros msg to publish. What you can do is use that Mat object to implement your own method this repo just provides a template for you.
