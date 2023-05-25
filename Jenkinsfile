pipeline {
    agent any

    stages {
    
        stage('Build') {
            
            steps{
            echo 'Building file...'
            sh 'g++ main.cpp'
            }
        }
        stage('Deploy') {
            when {
              expression {
                currentBuild.result == null || currentBuild.result == 'SUCCESS' 
              }
            }
            steps {
                echo 'Deploying...'
              
            }
        }
    }
    post {
        always {
        mail bcc: '', body: "<b>Example</b><br>Project: ${env.JOB_NAME} <br>Build Number: ${env.BUILD_NUMBER} <br> URL de build: ${env.BUILD_URL}", cc: '', charset: 'UTF-8', from: '', mimeType: 'text/html', replyTo: '', subject: "ERROR CI: Project name -> ${env.JOB_NAME}", to: "admir.mustafic@fet.ba";  

        }
    }
}
